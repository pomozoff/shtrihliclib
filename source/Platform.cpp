
#include "stdafx.h"

#include "Platform.h"
#include "PlatformLinux.h"
#include "PlatformWindows.h"

#pragma region Constructor Destructor
Platform::Platform(const std::wstring computer_name, const std::wstring user_name) :
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
const std::wstring Platform::session_id(void) const {

	return _computer_name + L"-" + _user_name;
}
#pragma endregion
