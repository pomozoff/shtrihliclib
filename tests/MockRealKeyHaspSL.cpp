
#include "stdafx.h"

#include <iterator>

#include "MockRealKeyHaspSL.h"
#include "ProtectKeyHaspSL.h"

static const hasp_handle_t HASP_HANDLE_VALUE = 10;
static const size_t LICENSES_AMOUNT = 2;

#pragma region Constructor Destructor
MockRealKeyHaspSL::MockRealKeyHaspSL(const hasp_feature_t feature_id) :
_feature_id(feature_id)
{
	initialize_ro_memory(_ro_buffer);
	initialize_rw_memory(_rw_buffer);
}
MockRealKeyHaspSL::~MockRealKeyHaspSL() {
}
#pragma endregion Constructor Destructor

#pragma region IRealKeyHasp
const hasp_status_t MockRealKeyHaspSL::_hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const {
	auto status = HASP_HASP_NOT_FOUND;
	if (feature_id == _feature_id) {
		status = HASP_STATUS_OK;
		handle = HASP_HANDLE_VALUE;
	} else {
		status = HASP_FEATURE_NOT_FOUND;
		handle = HASP_INVALID_HANDLE_VALUE;
	}
	_last_status = status;
	return status;
}
const hasp_status_t MockRealKeyHaspSL::_hasp_read(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const int length, value_t& buffer) const {
	value_t* local_buffer = nullptr;
	auto status = check_memory(handle, file_id, offset, length, buffer, &local_buffer);
	if (HASP_STATUS_OK != status) {
		return status;
	}
	buffer.assign(local_buffer->begin() + offset, local_buffer->begin() + offset + length);

	status = HASP_STATUS_OK;
	_last_status = status;
	return status;
}
const hasp_status_t MockRealKeyHaspSL::_hasp_write(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const int length, const value_t& buffer) const {
	value_t* local_buffer = nullptr;
	auto status = check_memory(handle, file_id, offset, length, buffer, &local_buffer);
	if (HASP_STATUS_OK != status) {
		return status;
	}
	std::copy(buffer.begin(), buffer.end(), local_buffer->begin() + offset);

	status = HASP_STATUS_OK;
	_last_status = status;
	return status;
}
const hasp_status_t MockRealKeyHaspSL::_hasp_logout(const hasp_handle_t handle) const {
	auto status = HASP_STATUS_OK;
	_last_status = status;
	return status;
}
const hasp_status_t MockRealKeyHaspSL::_hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const {
	return HASP_STATUS_OK;
}
#pragma endregion IRealKeyHasp

const hasp_status_t MockRealKeyHaspSL::check_memory(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const int length, const value_t& buffer, value_t** local_buffer) const {
	if (HASP_HANDLE_VALUE != handle) {
		return HASP_INV_HND;
	}
	switch (file_id) {
	case HASP_FILEID_RO:
		*local_buffer = &_ro_buffer;
		break;
	case HASP_FILEID_RW:
		*local_buffer = &_rw_buffer;
		break;
	default:
		return HASP_INV_FILEID;
		break;
	}
	if ((*local_buffer)->size() < (offset + length)) {
		return HASP_MEM_RANGE;
	}
	return HASP_STATUS_OK;
}
void MockRealKeyHaspSL::initialize_ro_memory(value_t& buffer) const {
	const size_t one_byte = 256;
	if (LICENSES_AMOUNT > (one_byte^2)) {
		value_t init_value;
		buffer = init_value;
		return;
	}
	value_t init_value(ProtectKeyHaspSL::read_only_memory_size, 0);

	init_value[ProtectKeyHaspSL::offset_licenses_amount + 0] = LICENSES_AMOUNT / one_byte;
	init_value[ProtectKeyHaspSL::offset_licenses_amount + 1] = LICENSES_AMOUNT % one_byte;

	std::copy(_ro_memory_value.begin(), _ro_memory_value.end(), init_value.begin() + _ro_memory_offset);

	buffer = init_value;
}
void MockRealKeyHaspSL::initialize_rw_memory(value_t& buffer) const {
	value_t init_value(ProtectKeyHaspSL::read_write_memory_size, 0);
	buffer = init_value;
}
