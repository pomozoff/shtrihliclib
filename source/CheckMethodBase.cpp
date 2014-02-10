
#include "stdafx.h"

#include "CheckMethodBase.h"
#include "KeyChecker.h"

CheckMethodBase::CheckMethodBase(void) {
}
CheckMethodBase::~CheckMethodBase(void) {
}

const bool CheckMethodBase::check(const std::shared_ptr<const IKeyChecker> key_checker) const {
	std::shared_ptr<const CheckMethodBase> sp_this = shared_from_this();
	bool logged_in = key_checker->is_base_key_available(sp_this);
	return false;
};
