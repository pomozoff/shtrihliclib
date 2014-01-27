
#include "StdAfx.h"
#include "CheckMethodBase.h"
#include "IKeyChecker.h"

CheckMethodBase::CheckMethodBase(void) {
}
CheckMethodBase::~CheckMethodBase(void) {
}

bool CheckMethodBase::check(IKeyChecker key_checker) {
	return false;
};
