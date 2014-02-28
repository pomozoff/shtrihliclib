
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

ProtectKeyHaspSL::ProtectKeyHaspSL(void) :
_key_number(R"()")
{
#pragma region Constructor Destructor
}
ProtectKeyHaspSL::~ProtectKeyHaspSL(void) {
}
#pragma endregion Constructor Destructor

#pragma region ProtectKey Interface
const value_t ProtectKeyHaspSL::read_memory(const check_method_memory_t check_method) const {
	value_t value;
	const hasp_handle_t handle = get_handle(check_method->logged_in_method());
	if (HASP_INVALID_HANDLE_VALUE != handle) {
		auto offset = check_method->offset();
		auto length = check_method->value().size();
		hasp_status_t status = _hasp_read(handle, HASP_FILEID_RO, offset, length, value);
	}
	return value;
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

const hasp_handle_t ProtectKeyHaspSL::get_handle(const check_method_login_t check_method) const {
#pragma region KeyChecker Interface
	auto iterator = _handles.find(check_method);
	return iterator == _handles.end() ? HASP_INVALID_HANDLE_VALUE : iterator->second;
}
const hasp_status_t ProtectKeyHaspSL::_hasp_login(const hasp_feature_t feature_id, const hasp_vendor_code_t vendor_code, hasp_handle_t handle) const {
	return hasp_login_scope(feature_id, scope, vendor_code, &handle);
#pragma endregion KeyChecker Interface

#pragma region Private
}
const hasp_status_t ProtectKeyHaspSL::_hasp_read(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, value_t& buffer) const {
	uint8_t *data = new uint8_t[length];
	hasp_status_t status = hasp_read(handle, file_id, offset, length, data);

	if (HASP_STATUS_OK == status) {
		buffer.assign(data[0], data[length - 1]);
	}
	delete[] data;

	return status;
}
const hasp_status_t ProtectKeyHaspSL::_hasp_write(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, const value_t& buffer) const {
	return hasp_write(handle, file_id, offset, length, &buffer[0]);
}
const hasp_status_t ProtectKeyHaspSL::_hasp_logout(const hasp_handle_t handle) const {
	return hasp_logout(handle);
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
	return false;
}
const size_t ProtectKeyHaspSL::licenses_amount(const check_method_login_t check_method) const {
	value_t buffer(2);
	auto check_method_memory = create_check_method_memory(offset_licenses_amount, buffer, check_method);
	return 0;
}
const bool ProtectKeyHaspSL::get_license(const check_method_login_t check_method) const {
	return false;
}

void ProtectKeyHaspSL::free_licnese(void) const {

}
#pragma endregion Private
