
#include "stdafx.h"

#include "PlatformWindows.h"

#pragma region Constructor Destructor
PlatformWindows::PlatformWindows(void) :
Platform(get_computer_name(), get_user_name())
{
}
PlatformWindows::~PlatformWindows(void) {
}
#pragma endregion

#pragma region Private
const std::wstring PlatformWindows::get_computer_name(void) const {
}
const std::wstring PlatformWindows::get_user_name(void) const {
}
#pragma endregion
