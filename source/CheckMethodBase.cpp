
#include "StdAfx.h"
#include "CheckMethodBase.h"
#include "IKeyChecker.h"

CheckMethodBase::CheckMethodBase(void) {
}
CheckMethodBase::~CheckMethodBase(void) {
}

bool CheckMethodBase::check(const IKeyChecker* key_checker) {
	return false;
};
check_method_t CheckMethodBase::check_method_type(void) {
	return CHECK_METHOD_BASE;
}
