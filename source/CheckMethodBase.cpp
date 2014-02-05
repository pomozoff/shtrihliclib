
#include "stdafx.h"
#include "CheckMethodBase.h"
#include "IKeyChecker.h"

CheckMethodBase::CheckMethodBase(void) {
	m_check_method = CHECK_METHOD_BASE;
}
CheckMethodBase::~CheckMethodBase(void) {
}

bool const CheckMethodBase::check(const IKeyChecker& key_checker) const {
	return false;
};
