
#include "stdafx.h"

#include "RealKeyRockeyNet.h"

using net_rockey_t = uint16_t(__stdcall *)(uint16_t function, uint16_t* handle, uint32_t* lp1, uint32_t* lp2, uint16_t* p1, uint16_t* p2, uint16_t* p3, uint16_t* p4, uint8_t* buffer);
using set_ini_path_t = uint16_t(__stdcall *)(const char* path);

#pragma region Constructor Destructor
RealKeyRockeyNet::RealKeyRockeyNet(void)
	: RealKeyRockeyNet(NULL)
{
}
RealKeyRockeyNet::RealKeyRockeyNet(char* ini_path)
	: _is_terminal_mode(is_terminal_mode_detected())
	, _library_handle(load_library(L"NrClient.dll"))
	, _net_rockey_function_pointer(get_function_pointer(_library_handle, "NetRockey"))
	, _set_ini_path_function_pointer(get_function_pointer(_library_handle, "SetIniPathName"))
{
	if (ini_path != NULL && _set_ini_path_function_pointer != NULL) {
		set_ini_path_t set_ini_path_function_pointer = (set_ini_path_t)_set_ini_path_function_pointer;
		set_ini_path_function_pointer(ini_path);
	}
}
RealKeyRockeyNet::~RealKeyRockeyNet(void) {
	if (!_library_handle) {
		FreeLibrary(_library_handle);
	}
}
#pragma endregion

#pragma region Protected
const size_t RealKeyRockeyNet::max_memory_size(void) const {
	return _memory_size;
}
const rockey_long_t RealKeyRockeyNet::prepared_feature_id(const rockey_feature_t feature_id) const {
	return feature_id + (_is_terminal_mode ? 0 : 0x10000);
}
const uint16_t RealKeyRockeyNet::call_rockey(uint16_t function, uint16_t* handle, uint32_t* lp1, uint32_t* lp2, uint16_t* p1, uint16_t* p2, uint16_t* p3, uint16_t* p4, uint8_t* buffer) const {
	if (!_net_rockey_function_pointer) {
		return ERR_NO_DRIVER;
	}
	net_rockey_t net_rockey_function_pointer = (net_rockey_t)_net_rockey_function_pointer;
	return net_rockey_function_pointer(function, handle, lp1, lp2, p1, p2, p3, p4, buffer);
}
#pragma endregion

#pragma region Private
const bool RealKeyRockeyNet::is_terminal_mode_detected(void) const {
	return GetSystemMetrics(SM_REMOTESESSION) > 0;
}
const HINSTANCE RealKeyRockeyNet::load_library(const LPCWCH library_name) const {
	HINSTANCE library_handle = GetModuleHandle(library_name);
	if (library_handle == NULL) {
		library_handle = LoadLibrary(library_name);
	}
	return library_handle;
}
const FARPROC RealKeyRockeyNet::get_function_pointer(const HINSTANCE library_handle, const char* function_name) const {
	return library_handle != NULL ? GetProcAddress(library_handle, function_name) : NULL;
}
#pragma endregion
