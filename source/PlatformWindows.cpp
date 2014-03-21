
#include "stdafx.h"

#include "PlatformWindows.h"

#pragma region Constructor Destructor
PlatformWindows::PlatformWindows(void) :
Platform(get_computer_name(), get_user_name())
{
}
PlatformWindows::~PlatformWindows(void) {
}
#pragma endregion Constructor Destructor

#pragma region Private
const std::string PlatformWindows::get_computer_name(void) const {
	// TODO: Добавить реализацию получения имени компьютера
	return R"(windows-computer)";
}
const std::string PlatformWindows::get_user_name(void) const {
	// TODO: Добавить реализацию получения имени пользователя
	return R"(windows-user)";
}
#pragma endregion Private
