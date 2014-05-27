
#include "stdafx.h"

#include "RealKeyRockey.h"

static const rockey_pass_t pass1 = 0x12;
static const rockey_pass_t pass2 = 0x303;
static const rockey_pass_t pass3 = 0;
static const rockey_pass_t pass4 = 0;

#pragma region Constructor Destructor
RealKeyRockey::RealKeyRockey(void) {
}
RealKeyRockey::~RealKeyRockey(void) {
}
#pragma endregion

#pragma region Public
const rockey_status_t RealKeyRockey::_rockey_login(const rockey_feature_t feature_id, std::string& key_number, rockey_handle_t& handle) const {
	rockey_keys_t keys;
	rockey_status_t status = find_keys(keys);
	if (ERR_SUCCESS == status) {
		rockey_function_t function = RY_OPEN;
		rockey_handle_t handle = 0;
		rockey_long_t lp1 = 0;
		rockey_long_t lp2 = 0;
		rockey_pass_t p1 = pass1;
		rockey_pass_t p2 = pass2;
		rockey_pass_t p3 = 0;
		rockey_pass_t p4 = 0;
		uint8_t buffer[memory_size_rockey4_net];

		for (auto&& key_id : keys) {
			function = RY_OPEN;
			lp1 = key_id;
			lp2 = prepared_feature_id(feature_id);
			std::memset(&buffer[0], 0, memory_size_rockey4_net);
			p2 = pass2;
			status = Rockey(function, &handle, &lp1, &lp2, &p1, &p2, &p3, &p4, &buffer[0]);
			if (ERR_SUCCESS == status) {
				_key_type = lp2;
				function = RY_CHECK_MOUDLE;
				p1 = feature_id;
				status = ((ERR_SUCCESS == Rockey(function, &handle, &lp1, &lp2, &p1, &p2, &p3, &p4, &buffer[0])) && (1 == p2)) ? ERR_SUCCESS : ERR_NO_ROCKEY;
				if (ERR_SUCCESS == status) {
					break;
				}
			}
			_rockey_logout(handle);
		}
	}
	return status;
}
const rockey_status_t RealKeyRockey::_rockey_read(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const {
	return ERR_INVALID_HANDLE;
}
const rockey_status_t RealKeyRockey::_rockey_write(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const {
	return ERR_INVALID_HANDLE;
}
const rockey_status_t RealKeyRockey::_rockey_logout(const rockey_handle_t handle) const {
	rockey_function_t function = RY_CLOSE;
	rockey_handle_t local_handle = handle;
	rockey_long_t lp1 = 0;
	rockey_long_t lp2 = 0;
	rockey_pass_t p1 = pass1;
	rockey_pass_t p2 = pass2;
	rockey_pass_t p3 = 0;
	rockey_pass_t p4 = 0;
	uint8_t buffer[memory_size_rockey4_net];

	rockey_status_t status = Rockey(function, &local_handle, &lp1, &lp2, &p1, &p2, &p3, &p4, &buffer[0]);
	return status;
}
#pragma endregion

#pragma region Private
const rockey_status_t RealKeyRockey::find_keys(rockey_keys_t& keys) const {
	keys.clear();

	rockey_status_t status = ERR_NO_ROCKEY;
	rockey_function_t function = RY_FIND;
	rockey_handle_t handle = 0;
	rockey_long_t lp1 = 0;
	rockey_long_t lp2 = 0;
	rockey_pass_t p1 = pass1;
	rockey_pass_t p2 = pass2;
	rockey_pass_t p3 = 0;
	rockey_pass_t p4 = 0;
	uint8_t buffer[memory_size_rockey4_net];

	while (ERR_SUCCESS == Rockey(function, &handle, &lp1, &lp2, &p1, &p2, &p3, &p4, &buffer[0])) {
		status = ERR_SUCCESS;
		function = RY_FIND_NEXT;
		p1 = pass1;
		p2 = pass2;
		keys.push_back(lp1);
	}
	return status;
}
#pragma endregion
