
#include "stdafx.h"

#include "RealKeyHaspHL.h"

#pragma region Constructor Destructor
RealKeyHaspHL::RealKeyHaspHL(void) {
}
RealKeyHaspHL::~RealKeyHaspHL(void) {
}
#pragma endregion

#pragma region RealKeyHasp
const hasp_status_t RealKeyHaspHL::_hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const {
	(void)scope;
	auto status = hasp_login(feature_id, vendor_code, &handle);
	_last_status = status;
	return status;
}
#pragma endregion
