
#include "stdafx.h"

#include "RealKeyHasp.h"

#pragma region Constructor Destructor
RealKeyHasp::RealKeyHasp(void) {
}
RealKeyHasp::~RealKeyHasp(void) {
	hasp_cleanup();
}
#pragma endregion

#pragma region Public
const hasp_status_t RealKeyHasp::_hasp_read(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const {
	byte_t *data = new byte_t[length];
	auto status = hasp_read(handle, file_id, offset, length, data);
	_last_status = status;

	if (HASP_STATUS_OK == status) {
		buffer.assign(&data[0], &data[length]);
	}
	delete[] data;

	return status;
}
const hasp_status_t RealKeyHasp::_hasp_write(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const {
	auto status = hasp_write(handle, file_id, offset, length, &buffer[0]);
	_last_status = status;
	return status;
}
const hasp_status_t RealKeyHasp::_hasp_logout(const hasp_handle_t handle) const {
	auto status = hasp_logout(handle);
	_last_status = status;
	return status;
}
const hasp_status_t RealKeyHasp::_hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const {
	return hasp_legacy_set_idletime(handle, idle_time);
}
const hasp_status_t RealKeyHasp::_hasp_decrypt(const hasp_handle_t handle, byte_t* buffer, const hasp_size_t length) const {
	auto status = hasp_decrypt(handle, (void*)buffer, length);
	_last_status = status;

	return status;
}
#pragma endregion

#pragma region Accessors
const hasp_status_t RealKeyHasp::last_status(void) const {
	return _last_status;
}
#pragma endregion
