
#include "stdafx.h"

#include <iterator>

#include "MockRealKeyHaspSL.h"
#include "ProtectKeyHaspSL.h"
#include "CheckMethodMemory.h"

static const hasp_handle_t HASP_HANDLE_VALUE = 10;

#pragma region Constructor Destructor
MockRealKeyHaspSL::MockRealKeyHaspSL(const hasp_feature_t feature_id, const check_methods_memory_t check_methods_memory) :
_feature_id(feature_id)
{
	initialize_memory(check_methods_memory);
}
MockRealKeyHaspSL::~MockRealKeyHaspSL() {
}
#pragma endregion

#pragma region Public
void MockRealKeyHaspSL::set_licenses_amount(const size_t amount) const {
	const size_t one_byte = 0xff;
	_ro_buffer[ProtectKeyHaspSL::offset_licenses_amount + 0] = amount / one_byte;
	_ro_buffer[ProtectKeyHaspSL::offset_licenses_amount + 1] = amount % one_byte;
}
const size_t MockRealKeyHaspSL::licenses_amount(void) const {
	return _ro_buffer[ProtectKeyHaspSL::offset_licenses_amount + 0] * 0xff + _ro_buffer[ProtectKeyHaspSL::offset_licenses_amount + 1];
}
#pragma endregion

#pragma region RealKeyHasp
const hasp_status_t MockRealKeyHaspSL::_hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const {
	auto status = HASP_HASP_NOT_FOUND;
	if (!is_enabled()) {
		return status;
	}
	handle = HASP_INVALID_HANDLE_VALUE;
	if (_feature_id == feature_id) {
		if (add_logged_in_user()) {
			status = HASP_STATUS_OK;
			handle = HASP_HANDLE_VALUE;
		} else {
			status = HASP_TOO_MANY_USERS;
		}
	} else {
		status = HASP_FEATURE_NOT_FOUND;
	}
	_last_status = status;
	return status;
}
const hasp_status_t MockRealKeyHaspSL::_hasp_read(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const {
	auto status = HASP_HASP_NOT_FOUND;
	if (!is_enabled()) {
		return status;
	}
	value_t* local_buffer = nullptr;
	status = check_memory(handle, file_id, offset, length, buffer, &local_buffer);
	if (HASP_STATUS_OK != status) {
		return status;
	}
	buffer.assign(local_buffer->begin() + offset, local_buffer->begin() + offset + length);

	status = HASP_STATUS_OK;
	_last_status = status;
	return status;
}
const hasp_status_t MockRealKeyHaspSL::_hasp_write(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const {
	auto status = HASP_HASP_NOT_FOUND;
	if (!is_enabled()) {
		return status;
	}
	value_t* local_buffer = nullptr;
	status = check_memory(handle, file_id, offset, length, buffer, &local_buffer);
	if (HASP_STATUS_OK != status) {
		return status;
	}
	std::copy(buffer.begin(), buffer.end(), local_buffer->begin() + offset);

	status = HASP_STATUS_OK;
	_last_status = status;
	return status;
}
const hasp_status_t MockRealKeyHaspSL::_hasp_logout(const hasp_handle_t handle) const {
	auto status = HASP_HASP_NOT_FOUND;
	if (!is_enabled()) {
		return status;
	}
	if (HASP_HANDLE_VALUE == handle) {
		status = HASP_STATUS_OK;
		del_logged_in_user();
	} else {
		status = HASP_INV_HND;
	}
	_last_status = status;
	return status;
}
const hasp_status_t MockRealKeyHaspSL::_hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const {
	auto status = HASP_HASP_NOT_FOUND;
	if (!is_enabled()) {
		return status;
	}
	return HASP_STATUS_OK;
}
#pragma endregion

#pragma region Private
void MockRealKeyHaspSL::initialize_memory(const check_methods_memory_t& check_methods_memory) const {
	_ro_buffer.assign(ProtectKeyHaspSL::read_only_memory_size,  0);
	_rw_buffer.assign(ProtectKeyHaspSL::read_write_memory_size, 0);

	for (auto&& check_method_memory : check_methods_memory) {
		auto key_memory_type = check_method_memory->memory_type();
		auto buffer = get_buffer_by_memory_type(hasp_memory_type(key_memory_type));
		if (nullptr == buffer) {
			continue;
		}
		auto& value = check_method_memory->value();
		auto offset = check_method_memory->offset();
		std::copy(value.begin(), value.end(), buffer->begin() + offset);
	}
}
const hasp_status_t MockRealKeyHaspSL::check_memory(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const int length, const value_t& buffer, value_t** local_buffer) const {
	if (HASP_HANDLE_VALUE != handle) {
		return HASP_INV_HND;
	}
	*local_buffer = get_buffer_by_memory_type(file_id);
	if (nullptr == *local_buffer) {
		return HASP_INV_FILEID;
	}
	if ((*local_buffer)->size() < (offset + length)) {
		return HASP_MEM_RANGE;
	}
	return HASP_STATUS_OK;
}
value_t* const MockRealKeyHaspSL::get_buffer_by_memory_type(const hasp_fileid_t file_id) const {
	value_t* result = nullptr;
	switch (file_id) {
	case HASP_FILEID_RO:
		result = &_ro_buffer;
		break;
	case HASP_FILEID_RW:
		result = &_rw_buffer;
		break;
	default:
		break;
	}
	return result;
}
#pragma endregion
