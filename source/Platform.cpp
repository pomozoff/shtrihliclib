
#include "stdafx.h"

#include "Platform.h"
#include "PlatformLinux.h"
#include "PlatformWindows.h"

#pragma region Constructor Destructor
Platform::Platform(const std::string computer_name, const std::string user_name) :
_computer_name(computer_name),
_user_name(user_name)
{
}
Platform::~Platform(void) {
}
#pragma endregion

#pragma region Public
const platform_t Platform::platform(void) {
#ifdef __linux__
	return std::make_shared<const PlatformLinux>();
#else
	return std::make_shared<const PlatformWindows>();
#endif // __linux__
}
#pragma endregion

#pragma region Accessors
const std::string Platform::computer_name(void) const {
	return _computer_name;
}
const std::string Platform::user_name(void) const {
	return _user_name;
}
#pragma endregion
