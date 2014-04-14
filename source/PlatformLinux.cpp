
#include "stdafx.h"

#include "PlatformLinux.h"

#pragma region Constructor Destructor
PlatformLinux::PlatformLinux(void) :
Platform(get_computer_name(), get_user_name())
{
}
PlatformLinux::~PlatformLinux(void) {
}
#pragma endregion

#pragma region Private
const std::wstring PlatformLinux::get_computer_name(void) const {
	// TODO: Добавить реализацию получения имени компьютера
	return L"(linux-computer)";
}
const std::wstring PlatformLinux::get_user_name(void) const {
	// TODO: Добавить реализацию получения имени пользователя
	return L"(linux-user)";
}
#pragma endregion
