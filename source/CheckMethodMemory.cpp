
#include "StdAfx.h"
#include "CheckMethodMemory.h"
#include "IKeyChecker.h"

CheckMethodMemory::CheckMethodMemory(const unsigned long offset, const unsigned char* value, const CheckMethodLogin* logged_in_method) {
}
CheckMethodMemory::~CheckMethodMemory(void) {
}

bool CheckMethodMemory::check(const IKeyChecker* key_checker) {
	return false;
};
check_method_t CheckMethodMemory::check_method_type(void) {
	return CHECK_METHOD_MEMORY;
}
