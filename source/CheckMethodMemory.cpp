
#include "StdAfx.h"
#include "CheckMethodMemory.h"
#include "IKeyChecker.h"

CheckMethodMemory::CheckMethodMemory(void) {
}
CheckMethodMemory::~CheckMethodMemory(void) {
}

bool CheckMethodMemory::check(const IKeyChecker* key_checker) {
	return false;
};

check_method_t CheckMethodMemory::check_method_type(void) {
	return CHECK_METHOD_MEMORY;
}
