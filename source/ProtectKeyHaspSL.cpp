
#include "stdafx.h"

#include "ProtectKeyHaspSL.h"
#include "CheckMethodMemory.h"
#include "CheckMethodLogin.h"

#include "DataTypes.h"

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
	"<haspscope/>";

static const offset_t offset_licenses_amount = 8;
#pragma endregion Constants

#pragma region Constructor Destructor
ProtectKeyHaspSL::ProtectKeyHaspSL(void) {
}
ProtectKeyHaspSL::~ProtectKeyHaspSL(void) {
	free_licnese();
}
#pragma endregion Constructor Destructor

#pragma region ProtectKey Interface
const value_t ProtectKeyHaspSL::read_memory(const check_method_memory_t check_method) const {
	value_t buffer;
	const hasp_handle_t handle = get_handle(check_method->logged_in_method());
	if (HASP_INVALID_HANDLE_VALUE != handle) {
		auto offset = check_method->offset();
		auto length = check_method->value().size();
		hasp_status_t status = _hasp_read(handle, HASP_FILEID_RO, offset, length, buffer);
	}
	return buffer;
}
#pragma endregion ProtectKey Interface

#pragma region IKeyChecker Interface
const bool ProtectKeyHaspSL::is_able_to_login(const check_method_login_t check_method) const {
	return false;
}
const bool ProtectKeyHaspSL::is_same_memory(const check_method_memory_t check_method) const {
	return false;
}
const bool ProtectKeyHaspSL::logout_key(const check_method_login_t check_method) const {
	return false;
}
#pragma endregion IKeyChecker Interface

#pragma region KeyChecker Interface
const handle_t ProtectKeyHaspSL::get_handle(const check_method_login_t check_method) const {
	auto iterator = _handles.find(check_method);
	return iterator == _handles.end() ? HASP_INVALID_HANDLE_VALUE : iterator->second;
}
void ProtectKeyHaspSL::remove_handle(const check_method_login_t check_method) const {
	const auto iterator = _handles.find(check_method);
	if (_handles.end() != iterator) {
		_handles.erase(iterator);
	}
}
#pragma endregion KeyChecker Interface

#pragma region Private
const hasp_status_t ProtectKeyHaspSL::_hasp_login_scope(const hasp_feature_t feature_id, const hasp_vendor_code_t vendor_code, hasp_handle_t handle) const {
	auto status = hasp_login_scope(feature_id, scope, vendor_code, &handle);
	_last_status = status;
	return status;
}
const hasp_status_t ProtectKeyHaspSL::_hasp_read(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, value_t& buffer) const {
	uint8_t *data = new uint8_t[length];
	auto status = hasp_read(handle, file_id, offset, length, data);
	_last_status = status;

	if (HASP_STATUS_OK == status) {
		buffer.assign(data[0], data[length - 1]);
	}
	delete[] data;

	return status;
}
const hasp_status_t ProtectKeyHaspSL::_hasp_write(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, const value_t& buffer) const {
	auto status = hasp_write(handle, file_id, offset, length, &buffer[0]);
	_last_status = status;
	return status;
}
const hasp_status_t ProtectKeyHaspSL::_hasp_logout(const hasp_handle_t handle) const {
	auto status = hasp_logout(handle);
	_last_status = status;
	return status;
}

const std::string ProtectKeyHaspSL::key_id(const hasp_handle_t handle) const {
	char *info = 0;
	std::string key_id = R"()", xml_begin_id = "<haspid>", xml_end_id = "</haspid>";
	const hasp_status_t status = hasp_get_sessioninfo(handle, HASP_KEYINFO, &info);
	if (HASP_STATUS_OK == status) {
		const std::string info_string = info;
		const size_t haspid_begin = info_string.find_first_of(xml_begin_id);
		const size_t haspid_end = info_string.find_first_of(xml_end_id);
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
		status = _hasp_read(handle, HASP_FILEID_RW, offset, length, buffer);
	}
	return status;
}
const hasp_status_t ProtectKeyHaspSL::write_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const {
	hasp_status_t status = HASP_INV_HND;
	const hasp_handle_t handle = get_handle(check_method);
	if (HASP_INVALID_HANDLE_VALUE != handle) {
		status = _hasp_write(handle, HASP_FILEID_RW, offset, length, buffer);
	}
	return status;
}

const bool ProtectKeyHaspSL::login(const check_method_login_t check_method) const {
	if (!check_method) {
		return false;
	}
	hasp_handle_t handle = HASP_INV_HND;
	const auto status = _hasp_login_scope(check_method->feature(), vendor_code, handle);
	const bool success = HASP_STATUS_OK == status;

	process_result(status);
	if (HASP_STATUS_OK == _last_status) {
		_key_number = key_id(handle);
		hasp_legacy_set_idletime(handle, 1);

		add_handle(check_method, handle);
		add_feature(check_method->feature());
	}
	return success;
}
const size_t ProtectKeyHaspSL::licenses_amount(const check_method_login_t check_method) const {
	const size_t sizeof_buffer = 2;
	const size_t one_byte = 256;

	value_t buffer(sizeof_buffer);
	auto check_method_memory = create_check_method_memory(offset_licenses_amount, buffer, check_method);
	auto data = read_memory(check_method_memory);

	size_t read_licenses_amount = 0;
	if (sizeof_buffer == data.size()) {
		read_licenses_amount = buffer[0] * one_byte + buffer[1];
	}
	return 0;
}
const license_block_manager_t ProtectKeyHaspSL::make_license_block_manager(const check_method_login_t check_method) const {
	value_t buffer;
	if (read_rw_memory(check_method, 0, read_write_memory_size, buffer) != HASP_STATUS_OK) {
		return nullptr;
	}
	auto license_block_manager = std::make_shared<const LicenseBlockManager>(buffer, license_timeout, licenses_amount(check_method));
	if (!license_block_manager) {
		return nullptr;
	}
	return license_block_manager;
}
const bool ProtectKeyHaspSL::get_license(const check_method_login_t check_method) const {
	auto license_block_manager = make_license_block_manager(check_method);
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
	if (!login(_last_loggedin_method)) {
		return;
	}
	auto license_block_manager = make_license_block_manager(_last_loggedin_method);
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
			_error_string = R"()";
			break;
		case HASP_NO_DRIVER:
			_error_string = R"(Не обнаружен драйвер HASP)";
			break;
		case HASP_CONTAINER_NOT_FOUND:
			_error_string = R"(Не найден ключ HASP)";
			break;
		case HASP_FEATURE_NOT_FOUND:
			_error_string = R"(Программа не найдена)";
			break;
		case HASP_TS_DETECTED:
			_error_string = R"(Запрещена работа в терминальной сессии)";
			break;
		case HASP_TMOF:
			_error_string = R"(Слишком много открытых программ)";
			break;
		case HASP_ACCESS_DENIED:
			_error_string = R"(Доступ к программе запрещён)";
			break;
		case HASP_OLD_DRIVER:
			_error_string = R"(Используется устаревший драйвер)";
			break;
		case HASP_SYS_ERR:
			_error_string = R"(Ошибка вызова системной функции)";
			break;
		case HASP_INSUF_MEM:
			_error_string = R"(Недостаточно памяти)";
			break;
		case HASP_INV_HND:
			_error_string = R"(Ошибочный дескриптор)";
			break;
		default:
			_error_string = R"(Ошибка)";
			break;
	}
}
#pragma endregion Private
