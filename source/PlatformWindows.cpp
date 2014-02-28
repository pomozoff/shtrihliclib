
#include "stdafx.h"

#include "PlatformWindows.h"

#pragma region Constructor Destructor
PlatformWindows::PlatformWindows(void) {
}
PlatformWindows::~PlatformWindows(void) {
}
#pragma endregion Constructor Destructor

#pragma region Accessors
const std::string PlatformWindows::computer_name(void) const {
	if (!_computer_name.empty()) {
		return _computer_name;
	}
	return R"()";
}
const std::string PlatformWindows::user_name(void) const {
	if (!_user_name.empty()) {
		return _user_name;
	}
	return R"()";
}
#pragma endregion Accessors
