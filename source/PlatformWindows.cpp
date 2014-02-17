
#include "stdafx.h"

#include "PlatformWindows.h"

PlatformWindows::PlatformWindows(void) {
}
PlatformWindows::~PlatformWindows(void) {
}

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
