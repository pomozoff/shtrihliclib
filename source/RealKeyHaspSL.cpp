
#include "stdafx.h"

#include "RealKeyHaspSL.h"

#pragma region Constructor Destructor
RealKeyHaspSL::RealKeyHaspSL(void) {
}
RealKeyHaspSL::~RealKeyHaspSL(void) {
}
#pragma endregion Constructor Destructor

const hasp_status_t RealKeyHaspSL::_hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const {
	auto status = hasp_login_scope(feature_id, scope, vendor_code, &handle);
	_last_status = status;
	return status;
}
const hasp_status_t RealKeyHaspSL::_hasp_read(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, value_t& buffer) const {
	uint8_t *data = new uint8_t[length];
	auto status = hasp_read(handle, file_id, offset, length, data);
	_last_status = status;

	if (HASP_STATUS_OK == status) {
		buffer.assign(data[0], data[length - 1]);
	}
	delete[] data;

	return status;
}
const hasp_status_t RealKeyHaspSL::_hasp_write(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, const value_t& buffer) const {
	auto status = hasp_write(handle, file_id, offset, length, &buffer[0]);
	_last_status = status;
	return status;
}
const hasp_status_t RealKeyHaspSL::_hasp_logout(const hasp_handle_t handle) const {
	auto status = hasp_logout(handle);
	_last_status = status;
	return status;
}
