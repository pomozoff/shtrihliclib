
#include "stdafx.h"

#include "ProtectKeyRockey.h"
#include "RealKeyRockey.h"
#include "CheckMethodMemory.h"
#include "CheckMethodLogin.h"
#include "LicenseBlock.h"
#include "LicenseBlockManager.h"

#pragma region Constructor Destructor
ProtectKeyRockey::ProtectKeyRockey(const real_key_rockey_t key, const KeyType keytype)
	: ProtectKey(keytype, _max_check_number)
	, _real_key(key)
{
}
ProtectKeyRockey::~ProtectKeyRockey(void) {
	logout(true);
}
#pragma endregion

#pragma region ProtectKey Interface
const value_t ProtectKeyRockey::read_memory(const check_method_memory_t check_method) const {
	value_t buffer;
	const rockey_handle_t handle = (rockey_handle_t)get_handle(check_method->logged_in_method());
	if (ROCKEY_INVALID_HANDLE_VALUE != handle) {
		const auto offset = (rockey_size_t)check_method->offset(); // It's OK
		const auto length = (rockey_size_t)check_method->value().size(); // It's OK

		buffer.resize(length);
		if (ERR_SUCCESS != _real_key->_rockey_read(handle, offset, length, buffer)) {
			buffer.clear();
		}
	}
	return buffer;
}
#pragma endregion

#pragma region IKeyChecker Interface
const bool ProtectKeyRockey::is_able_to_login(const check_method_login_t check_method) const {
	rockey_handle_t handle = ROCKEY_INVALID_HANDLE_VALUE;
	ProtectKey::is_able_to_login(check_method);
	bool isSuccess = login(check_method, handle) && ROCKEY_INVALID_HANDLE_VALUE != handle;
	if (isSuccess) {
		_last_loggedin_method = check_method;
	}
	return isSuccess;
}
const bool ProtectKeyRockey::is_same_memory(const check_method_memory_t check_method) const {
	bool success = false;
	auto buffer = read_memory(check_method);
	process_result(_real_key->last_status());
	if (ERR_SUCCESS == _real_key->last_status()) {
		_error_string = L"";
		if (check_method->value().size() == buffer.size()) {
			success = std::equal(buffer.begin(), buffer.end(), check_method->value().begin());
		}
	}
	return success;
}
const bool ProtectKeyRockey::logout_key(const check_method_login_t check_method) const {
	const rockey_handle_t handle = (rockey_handle_t)get_handle(check_method);
	return _real_key->_rockey_logout(handle) == ERR_SUCCESS;
}
#pragma endregion

#pragma region KeyChecker Interface
const key_handle_t ProtectKeyRockey::get_handle(const check_method_login_t check_method) const {
	auto iterator = _handles.find(check_method);
	return iterator == _handles.end() ? ROCKEY_INVALID_HANDLE_VALUE : iterator->second;
}
const check_number_t ProtectKeyRockey::max_check_number(void) const {
	return _max_check_number;
}
#pragma endregion

#pragma region Private
const rockey_status_t ProtectKeyRockey::read_memory(const check_method_login_t check_method, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const {
	(void)offset;
	(void)length;
	(void)buffer;
	return ERR_INVALID_HANDLE;
}
const rockey_status_t ProtectKeyRockey::write_memory(const check_method_login_t check_method, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const {
	(void)offset;
	(void)length;
	(void)buffer;
	return ERR_INVALID_HANDLE;
}

const bool ProtectKeyRockey::login(const check_method_login_t check_method, rockey_handle_t& handle) const {
	if (!check_method) {
		return false;
	}
	const auto rockey_feature = (rockey_feature_t)check_method->feature(); // It's OK
	const auto status = _real_key->_rockey_login(rockey_feature, _key_number, handle);
	const bool success = ERR_SUCCESS == status;

	process_result(status);
	if (success) {
		add_handle(check_method, handle);
	}
	return success;
}
const size_t ProtectKeyRockey::read_licenses_amount(const check_method_login_t check_method) const {
	return 0;
}
void ProtectKeyRockey::process_result(const rockey_status_t status) const {
	_error_code = status;
	switch (status)
	{
	case ERR_SUCCESS:
		_error_string = L"";
		break;
	case ERR_NO_DRIVER:
		_error_string = L"�� ��������� ������� ROCKEY";
		break;
	case ERR_NO_ROCKEY:
		_error_string = L"����������� ���� ROCKEY";
		break;
	case ERR_INVALID_PASSWORD:
		_error_string = L"������ ������� � �����";
		break;
	case ERR_INVALID_PASSWORD_OR_ID:
		_error_string = L"������ ����������� �����";
		break;
	case ERR_SETID:
		_error_string = L"������ ��������� HID";
		break;
	case ERR_INVALID_ADDR_OR_SIZE:
		_error_string = L"��������� ����� ������ �����";
		break;
	case ERR_UNKNOWN_COMMAND:
		_error_string = L"��������� �������";
		break;
	case ERR_NOTBELEVEL3:
		_error_string = L"���������� ������";
		break;
	case ERR_READ:
		_error_string = L"������ ������ ������ �����";
		break;
	case ERR_WRITE:
		_error_string = L"������ ������ ������ �����";
		break;
	case ERR_RANDOM:
		_error_string = L"������ ���������� ���������� ����� ���";
		break;
	case ERR_SEED:
		_error_string = L"������ ���������� ���������� ����� ���";
		break;
	case ERR_CALCULATE:
		_error_string = L"������ ����������";
		break;
	case ERR_NO_OPEN:
		_error_string = L"���� �� ������ ��� ��������";
		break;
	case ERR_OPEN_OVERFLOW:
		_error_string = L"������� ������� ����� ������ (����� 16)";
		break;
	case ERR_NOMORE:
		_error_string = L"���� ROCKEY �� ������";
		break;
	case ERR_NEED_FIND:
		_error_string = L"������ ��� ������ �����";
		break;
	case ERR_DECREASE:
		_error_string = L"������ ���������� �������� ������";
		break;
	case ERR_INVALID_HANDLE:
		_error_string = L"��������� ����������";
		break;
	case ERR_TS_DETECTED:
		_error_string = L"��������� ������ � ������������ ������";
		break;
	default:
		_error_string = L"������";
		break;
	}
}
#pragma endregion
