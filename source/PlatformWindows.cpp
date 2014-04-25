
#include "stdafx.h"

#define SECURITY_WIN32

#include <Windows.h>
#include <security.h>
#include <secext.h>

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
	DWORD size = 0;
	GetComputerNameExW(ComputerNameNetBIOS, NULL, &size);

	PTCHAR buffer = new TCHAR[size];
	std::wstring computerName = L"";
	if (GetComputerNameExW(ComputerNameNetBIOS, buffer, &size)) {
		computerName = buffer;
	}
	delete[] buffer;
	return computerName;
}
const std::wstring PlatformWindows::get_user_name(void) const {
	DWORD size = 0;
	GetUserNameExW(NameSamCompatible, NULL, &size);

	PTCHAR buffer = new TCHAR[size];
	std::wstring userName = L"";
	if (GetUserNameExW(NameSamCompatible, buffer, &size)) {
		userName = buffer;
	}
	delete[] buffer;
	return userName;
}
#pragma endregion
