
#include "stdafx.h"

#include "PlatformLinux.h"

#pragma region Constructor Destructor
PlatformLinux::PlatformLinux(void) :
Platform(get_computer_name(), get_user_name())
{
}
PlatformLinux::~PlatformLinux(void) {
}
#pragma endregion Constructor Destructor

#pragma region Private
const std::string PlatformLinux::get_computer_name(void) const {
	// TODO: Добавить реализацию получения имени компьютера
	return R"(linux-computer)";
}
const std::string PlatformLinux::get_user_name(void) const {
	// TODO: Добавить реализацию получения имени пользователя
	return R"(linux-user)";
}
#pragma endregion Private
