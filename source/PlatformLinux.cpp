
#include "stdafx.h"

#include "PlatformLinux.h"

#pragma region Constructor Destructor
PlatformLinux::PlatformLinux(void) {
}
PlatformLinux::~PlatformLinux(void) {
}
#pragma endregion Constructor Destructor

#pragma region Accessors
const std::string PlatformLinux::computer_name(void) const {
	if (!_computer_name.empty()) {
		return _computer_name;
	}
	return R"()";
}
const std::string PlatformLinux::user_name(void) const {
	if (!_user_name.empty()) {
		return _user_name;
	}
	return R"()";
}
#pragma endregion Accessors
