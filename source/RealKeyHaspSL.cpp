
#include "stdafx.h"

#include "RealKeyHaspSL.h"

#pragma region Constructor Destructor
RealKeyHaspSL::RealKeyHaspSL(void) {
}
RealKeyHaspSL::~RealKeyHaspSL(void) {
	hasp_cleanup();
}
#pragma endregion

#pragma region IRealKeyHasp
const hasp_status_t RealKeyHaspSL::_hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const {
	auto status = hasp_login_scope(feature_id, scope, vendor_code, &handle);
	_last_status = status;
	return status;
}
const hasp_status_t RealKeyHaspSL::_hasp_read(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const {
	uint8_t *data = new uint8_t[length];
	auto status = hasp_read(handle, file_id, offset, length, data);
	_last_status = status;

	if (HASP_STATUS_OK == status) {
		buffer.assign(&data[0], &data[length]);
	}
	delete[] data;

	return status;
}
const hasp_status_t RealKeyHaspSL::_hasp_write(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const {
	auto status = hasp_write(handle, file_id, offset, length, &buffer[0]);
	_last_status = status;
	return status;
}
const hasp_status_t RealKeyHaspSL::_hasp_logout(const hasp_handle_t handle) const {
	auto status = hasp_logout(handle);
	_last_status = status;
	return status;
}
const hasp_status_t RealKeyHaspSL::_hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const {
	return hasp_legacy_set_idletime(handle, idle_time);
}
const hasp_status_t RealKeyHaspSL::_hasp_decrypt(const hasp_handle_t handle, uint8_t* buffer, const hasp_size_t length) const {
	auto status = hasp_decrypt(handle, (void*)buffer, length);
	_last_status = status;

	return status;
}
#pragma endregion
