
#include "stdafx.h"

#include "Platform.h"
#include "PlatformLinux.h"
#include "PlatformWindows.h"

#pragma region Constructor Destructor
Platform::Platform(void) {
}
Platform::~Platform(void) {
}
#pragma endregion Constructor Destructor

#pragma region Public
const platform_t Platform::platform(void) {
#ifdef __linux__
	return std::make_shared<PlatformLinux>();
#else
	return std::make_shared<PlatformWindows>();
#endif // __linux__
}
#pragma endregion Public
