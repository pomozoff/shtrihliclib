
#include "stdafx.h"

#include "CheckMethodBase.h"
#include "KeyChecker.h"

#pragma region Constructor Destructor
CheckMethodBase::CheckMethodBase(void) :
CheckMethod(CheckMethodType::Base)
{
}
CheckMethodBase::~CheckMethodBase(void) {
}
#pragma endregion Constructor Destructor

#pragma region CheckMethod Interface
const bool CheckMethodBase::check(const ikey_checker_t key_checker) const {
	check_method_base_t sp_this = shared_from_this();
	bool logged_in = key_checker->is_base_key_available(sp_this);
	return false;
};
#pragma endregion CheckMethod Interface
