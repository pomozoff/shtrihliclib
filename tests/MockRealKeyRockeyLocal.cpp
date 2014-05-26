
#include "stdafx.h"

#include <iterator>

#include "MockRealKeyRockeyLocal.h"
#include "ProtectKeyRockey.h"
#include "CheckMethodMemory.h"

static const rockey_handle_t ROCKEY_HANDLE_VALUE = 77;

#pragma region Constructor Destructor
MockRealKeyRockeyLocal::MockRealKeyRockeyLocal(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory)
	: _feature_id(feature_id)
{
	initialize_memory(check_methods_memory);
}
MockRealKeyRockeyLocal::~MockRealKeyRockeyLocal() {
}
#pragma endregion

#pragma region RealKeyHasp
const rockey_status_t MockRealKeyRockeyLocal::_rockey_login(const rockey_feature_t feature_id, const rockey_passwords_t passwords, rockey_handle_t& handle) const {
	rockey_status_t status;
	if (feature_id == _feature_id) {
		status = ERR_SUCCESS;
		handle = ROCKEY_HANDLE_VALUE;
	} else {
		status = ERR_INVALID_FEATURE;
		handle = ROCKEY_INVALID_HANDLE_VALUE;
	}
	_last_status = status;
	return status;
}
const rockey_status_t MockRealKeyRockeyLocal::_rockey_read(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const {
	value_t* local_buffer = nullptr;
	auto status = check_memory(handle, offset, length, buffer, &local_buffer);
	if (ERR_SUCCESS != status) {
		return status;
	}
	buffer.assign(local_buffer->begin() + offset, local_buffer->begin() + offset + length);

	status = ERR_SUCCESS;
	_last_status = status;
	return status;
}
const rockey_status_t MockRealKeyRockeyLocal::_rockey_write(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const {
	value_t* local_buffer = nullptr;
	auto status = check_memory(handle, offset, length, buffer, &local_buffer);
	if (ERR_SUCCESS != status) {
		return status;
	}
	std::copy(buffer.begin(), buffer.end(), local_buffer->begin() + offset);

	status = ERR_SUCCESS;
	_last_status = status;
	return status;
}
const rockey_status_t MockRealKeyRockeyLocal::_rockey_logout(const rockey_handle_t handle) const {
	rockey_status_t status;
	if (ROCKEY_HANDLE_VALUE != handle) {
		status = ERR_INVALID_HANDLE;
	}
	else {
		status = ERR_SUCCESS;
	}
	_last_status = status;
	return status;
}
#pragma endregion

#pragma region Private
void MockRealKeyRockeyLocal::initialize_memory(const check_methods_memory_t& check_methods_memory) const {
	_buffer.assign(ProtectKeyRockey::memory_size_rockey4_local, 0);

	for (auto&& check_method_memory : check_methods_memory) {
		auto key_memory_type = check_method_memory->memory_type();
		auto& value = check_method_memory->value();
		auto offset = check_method_memory->offset();
		std::copy(value.begin(), value.end(), _buffer.begin() + offset);
	}
}
const rockey_status_t MockRealKeyRockeyLocal::check_memory(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer, value_t** local_buffer) const {
	if (ROCKEY_HANDLE_VALUE != handle) {
		return ERR_INVALID_HANDLE;
	}
	rockey_size_t last_position = (offset + length);
	if (_buffer.size() <= last_position) {
		return ERR_INVALID_MEM_RANGE;
	}
	return ERR_SUCCESS;
}
#pragma endregion
