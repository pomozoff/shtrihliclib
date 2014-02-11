
#include "stdafx.h"

#include "CheckMethodBase.h"
#include "KeyChecker.h"

CheckMethodBase::CheckMethodBase(void) {
}
CheckMethodBase::~CheckMethodBase(void) {
}

const bool CheckMethodBase::check(const ikey_checker_t key_checker) const {
	check_method_base_t sp_this = shared_from_this();
	bool logged_in = key_checker->is_base_key_available(sp_this);
	return false;
};
