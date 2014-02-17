
#include "stdafx.h"

#include "Platform.h"
#include "PlatformLinux.h"
#include "PlatformWindows.h"

Platform::Platform(void) {
}
Platform::~Platform(void) {
}

const platform_t Platform::platform(void) {
#ifdef __linux__
	return std::make_shared<PlatformLinux>();
#else
	return std::make_shared<PlatformWindows>();
#endif // __linux__
}
