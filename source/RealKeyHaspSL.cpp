
#include "stdafx.h"

#include "RealKeyHaspSL.h"

#pragma region Constructor Destructor
RealKeyHaspSL::RealKeyHaspSL(void) {
}
RealKeyHaspSL::~RealKeyHaspSL(void) {
	hasp_cleanup();
}
#pragma endregion

#pragma region RealKeyHasp
const hasp_status_t RealKeyHaspSL::_hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const {
	auto status = hasp_login_scope(feature_id, scope, vendor_code, &handle);
	_last_status = status;
	return status;
}
#pragma endregion
