
#include "stdafx.h"

#include "ProtectKeyHaspSL.h"
#include "CheckMethodMemory.h"
#include "CheckMethodLogin.h"
#include "RealKeyHasp.h"
#include "LicenseBlock.h"
#include "LicenseBlockManager.h"

#pragma region Constants
static const unsigned char vendor_code[] =
	"Ir8uIUvOt9rvL4GXELPf2KOnWon4Nt3J9XTOrpuM+4Kkhr5ClEoAoha6s2sCYx1UPtu0TfXK7pvO3rHN"
	"31lDHZlyMzZKj4O27bb5CkatSYi/L/g1x/yFDEAWN4tJYC1kY4OyItmJbCQ/4gzNXE/EgOA2WRhG677R"
	"e0LBuLuWfXvbhVnO1PPW+kqAcsaYHqxnQNlhF58MWybX/Y2li3dosA2Svr0p1PBRjnChlUNe4WWJnIJm"
	"vFs1RNzP4XXlqEx1Oah9nrOtGUOX7MUgkMRQCKBmHH3PSemIGyL7iTfhTdlnRJp2eCmuzCipf8bAk/OO"
	"BdlT1uj9ccUO3oaBMrGFcgPWgf1JelNeXvEtoVhspUVMk1865p5lDY4m68BtyvDQeRY7DOJCITScLeOi"
	"F53AkL1oe2mt3nF3rGnrrG4I6CsT7mcBX8oMSE0B0Qz6pA+NCJHYTxv8i0KZqkXlI5dJ4g4qT3AwMEAj"
	"F0aD5jtNFUgxcrx+k2CQhal099qVHk7IxzFjD2ExQ3iWriznAoHPUW6w3cYeHvataquCfkm/GJmhPmQ7"
	"VJa5z54ATzLBlnp7pSfiLt4G+wZoTe5yilBSjCpowCj3ESUW6urwFC7ZYDCTj9EZ0H9SqtcsWmO/T6gF"
	"lEgj3Zwrk6hJd/yx4lE2HBf6KiH4Gg+7+ChG8j+hAa5kATc9xPL6AoszyDnF4Ztq6uuV2F2la/7UBqPF"
	"AroEO5V5DQt1eTeNT1/4/T2ju3TO/F4AgDTm2+ovw2eW28VGuWiRGo3KvavY5uPI0paqcaFvDZGb7x1j"
	"8uxaQvVEA0pwMcPOqdT/9d1ZfRmpKxdVvVsH55D8PEnaHEUZ8arIBAMJTUbDGhRdw5xNkidF7eFUEBvP"
	"EShMnka+RgIOZHi31cxMPGe82hSedsutwyE6r+3X6L9ymvLBdWz5F/P+QVQ=";
static const char* scope = 
	"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
	"<haspscope>"
	"<hasp type = \"HASP-SL\"/>"
	"</haspscope>";

#pragma endregion

#pragma region Constructor Destructor
ProtectKeyHaspSL::ProtectKeyHaspSL(const real_key_hasp_t key, const size_t session_id_hash)
	: ProtectKey(KeyType::HaspSL, 0)
	, _session_id_hash(session_id_hash)
	, _real_key(key)
{
#ifdef _DEBUG
	_license_timeout = _key_polling_period_seconds;
#endif
}
ProtectKeyHaspSL::~ProtectKeyHaspSL(void) {
	free_licnese();
	logout(true);
}
#pragma endregion

#pragma region protect
void ProtectKeyHaspSL::init_key(void) const {
	_current_check_number = 0;
}
#pragma endregion

#pragma region ProtectKey Interface
const value_t ProtectKeyHaspSL::read_memory(const check_method_memory_t check_method) const {
	value_t buffer;
	const hasp_handle_t handle = get_handle(check_method->logged_in_method());
	if (HASP_INVALID_HANDLE_VALUE != handle) {
		auto offset = check_method->offset();
		auto length = check_method->value().size();
		auto memory_type = _real_key->hasp_memory_type(check_method->memory_type());
		buffer.resize(length);
		_real_key->_hasp_read(handle, memory_type, offset, length, buffer);
	}
	return buffer;
}
#pragma endregion

#pragma region IKeyChecker Interface
const bool ProtectKeyHaspSL::is_able_to_login(const check_method_login_t check_method) const {
	ProtectKey::is_able_to_login(check_method);
	bool isSuccess = false;
	hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
	if (login(check_method, handle)) {
		_key_number = key_id(handle);
		_last_loggedin_method = check_method;
		isSuccess = get_license(check_method);
	}
	return isSuccess;
}
const bool ProtectKeyHaspSL::is_same_memory(const check_method_memory_t check_method) const {
	bool success = false;
	auto buffer = read_memory(check_method);
	process_result(_real_key->last_status());
	if (HASP_STATUS_OK == _real_key->last_status()) {
		_error_string = L"";
		if (check_method->value().size() == buffer.size()) {
			success = std::equal(buffer.begin(), buffer.end(), check_method->value().begin());
		}
	}
	return success;
}
const bool ProtectKeyHaspSL::logout_key(const check_method_login_t check_method) const {
	bool success = false;
	const auto handle = get_handle(check_method);
	if (HASP_INVALID_HANDLE_VALUE == handle) {
		_error_string = L"Ошибка";
		_error_code = HASP_INVALID_HANDLE_VALUE;
	} else {
		const auto status = _real_key->_hasp_logout(handle);
		success = HASP_STATUS_OK == status;
		process_result(status);
	}
	return success;
}
/*
const bool ProtectKeyHaspSL::decrypt(byte_t* buffer, const size_t length) const {
	if (!_decrypt_method) {
		return false;
	}
	hasp_handle_t handle = get_handle(_decrypt_method);
	if (HASP_INVALID_HANDLE_VALUE == handle) {
		if (!login(_decrypt_method, handle)) {
			return false;
		}
	}
	auto status = _real_key->_hasp_decrypt(handle, buffer, length);
	return HASP_STATUS_OK == status;
}
*/
const std::string ProtectKeyHaspSL::get_key_type(void) const {
	return "Sentinel";
}
#pragma endregion

#pragma region KeyChecker Interface
const key_handle_t ProtectKeyHaspSL::get_handle(const check_method_login_t check_method) const {
	auto iterator = _handles.find(check_method);
	return iterator == _handles.end() ? HASP_INVALID_HANDLE_VALUE : iterator->second;
}
const check_number_t ProtectKeyHaspSL::max_check_number(void) const {
	return _max_check_number;
}
#pragma endregion

#pragma region Private
const std::string ProtectKeyHaspSL::key_id(const hasp_handle_t handle) const {
	char *info = NULL;
	std::string key_id = R"()";
	const std::string xml_begin_id = "<haspid>";
	const std::string xml_end_id = "</haspid>";
	const hasp_status_t status = hasp_get_sessioninfo(handle, HASP_KEYINFO, &info);
	if (HASP_STATUS_OK == status) {
		const std::string info_string = info;
		const size_t haspid_begin = info_string.find(xml_begin_id);
		const size_t haspid_end = info_string.find(xml_end_id);
		if (std::string::npos != haspid_begin && std::string::npos != haspid_end) {
			size_t first_symbol_position = haspid_begin + xml_begin_id.size();
			size_t length = haspid_end - first_symbol_position;
			key_id = info_string.substr(first_symbol_position, length);
		}
	}
	return key_id;
}

const hasp_status_t ProtectKeyHaspSL::read_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const {
	hasp_status_t status = HASP_INV_HND;
	const hasp_handle_t handle = get_handle(check_method);
	if (HASP_INVALID_HANDLE_VALUE != handle) {
		status = _real_key->_hasp_read(handle, HASP_FILEID_RW, offset, length, buffer);
	}
	return status;
}
const hasp_status_t ProtectKeyHaspSL::write_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const {
	hasp_status_t status = HASP_INV_HND;
	const hasp_handle_t handle = get_handle(check_method);
	if (HASP_INVALID_HANDLE_VALUE != handle) {
		status = _real_key->_hasp_write(handle, HASP_FILEID_RW, offset, length, buffer);
	}
	return status;
}

const bool ProtectKeyHaspSL::login(const check_method_login_t check_method, hasp_handle_t& handle) const {
	if (!check_method) {
		return false;
	}
	const auto status = _real_key->_hasp_login_scope(check_method->feature(), scope, vendor_code, handle);
	const bool success = HASP_STATUS_OK == status;

	process_result(status);
	if (success) {
		_real_key->_hasp_legacy_set_idletime(handle, 1);
		add_handle(check_method, handle);
	} else if (_first_key_check && status != HASP_TOO_MANY_USERS) {
		_current_check_number = _max_check_number;
	}
	return success;
}
const size_t ProtectKeyHaspSL::read_licenses_amount(const check_method_login_t check_method) const {
	const size_t sizeof_buffer = 2;
	const size_t one_byte = 256;

	value_t buffer(sizeof_buffer);
	auto check_method_memory = std::make_shared<const CheckMethodMemory>(offset_licenses_amount, buffer, check_method);
	auto data = read_memory(check_method_memory);

	_licenses_amount = 0;
	if (sizeof_buffer == data.size()) {
		_licenses_amount = data[0] * one_byte + data[1];
	}
	return _licenses_amount;
}
const license_block_manager_t ProtectKeyHaspSL::make_license_block_manager(const check_method_login_t check_method, const time_t loggedin_period_seconds) const {
	value_t buffer(read_write_memory_size);
	if (read_rw_memory(check_method, 0, read_write_memory_size, buffer) != HASP_STATUS_OK) {
		return nullptr;
	}
	auto license_block_manager = std::make_shared<const LicenseBlockManager>(buffer, loggedin_period_seconds, read_licenses_amount(check_method), _session_id_hash);
	return license_block_manager;
}
const bool ProtectKeyHaspSL::get_license(const check_method_login_t check_method) const {
	auto license_block_manager = make_license_block_manager(check_method, get_random_timeout_seconds());
	if (!license_block_manager) {
		return false;
	}
	auto license_block = license_block_manager->take_license();
	bool success = nullptr != license_block;
	if (success) {
		success = HASP_STATUS_OK == write_rw_memory(check_method, license_block->offset_in_manager(), license_block->sizeof_block, license_block->block());
	}
	return success;
}

void ProtectKeyHaspSL::free_licnese(void) const {
	hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
	if (!login(_last_loggedin_method, handle)) {
		return;
	}
	auto license_block_manager = make_license_block_manager(_last_loggedin_method, 0);
	if (!license_block_manager) {
		return;
	}
	auto license_block = license_block_manager->find_my_block();
	if (!license_block) {
		return;
	}
	license_block->make_expired();
	write_rw_memory(_last_loggedin_method, license_block->offset_in_manager(), license_block->sizeof_block, license_block->block());

	logout_key(_last_loggedin_method);
}
void ProtectKeyHaspSL::process_result(const hasp_status_t status) const {
	_error_code = status;
	switch (status)
	{
		case HASP_STATUS_OK:
			_error_string = L"";
			break;
		case HASP_NO_DRIVER:
			_error_string = L"Не обнаружен драйвер HASP";
			break;
		case HASP_TOO_MANY_USERS:
			_error_string = L"Ключ занят другим пользователем";
			break;
		case HASP_CONTAINER_NOT_FOUND:
			_error_string = L"Не найден ключ HASP";
			break;
		case HASP_FEATURE_NOT_FOUND:
			_error_string = L"Программа не найдена";
			break;
		case HASP_TS_DETECTED:
			_error_string = L"Запрещена работа в терминальной сессии";
			break;
		case HASP_TMOF:
			_error_string = L"Слишком много открытых программ";
			break;
		case HASP_ACCESS_DENIED:
			_error_string = L"Доступ к программе запрещён";
			break;
		case HASP_OLD_DRIVER:
			_error_string = L"Используется устаревший драйвер";
			break;
		case HASP_SYS_ERR:
			_error_string = L"Ошибка вызова системной функции";
			break;
		case HASP_INSUF_MEM:
			_error_string = L"Недостаточно памяти";
			break;
		case HASP_INV_HND:
			_error_string = L"Ошибочный дескриптор";
			break;
		default:
			_error_string = L"Ошибка";
			break;
	}
}
const time_t ProtectKeyHaspSL::get_random_timeout_seconds(void) const {
	return (_max_check_number * _key_polling_period_seconds + (std::rand() % _key_polling_period_seconds + 1));
}
#pragma endregion
