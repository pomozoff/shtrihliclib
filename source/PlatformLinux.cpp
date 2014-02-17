
#include "stdafx.h"

#include "PlatformLinux.h"

PlatformLinux::PlatformLinux(void) {
}
PlatformLinux::~PlatformLinux(void) {
}

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
