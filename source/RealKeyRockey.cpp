
#include "stdafx.h"

#include "RealKeyRockey.h"

#pragma region Constructor Destructor
RealKeyRockey::RealKeyRockey(void) {
}
RealKeyRockey::~RealKeyRockey(void) {
}
#pragma endregion

#pragma region Public
const rockey_status_t RealKeyRockey::_rockey_login(const rockey_feature_t feature_id, const rockey_passwords_t passwords, rockey_handle_t& handle) const {
	return ERR_INVALID_HANDLE;
}
const rockey_status_t RealKeyRockey::_rockey_read(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const {
	return ERR_INVALID_HANDLE;
}
const rockey_status_t RealKeyRockey::_rockey_write(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const {
	return ERR_INVALID_HANDLE;
}
const rockey_status_t RealKeyRockey::_rockey_logout(const rockey_handle_t handle) const {
	return ERR_INVALID_HANDLE;
}
#pragma endregion
