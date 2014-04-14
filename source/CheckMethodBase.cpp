
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
#pragma endregion

#pragma region CheckMethod Interface
const bool CheckMethodBase::check(const ikey_checker_t key_checker) const {
	return key_checker->is_base_key_available(shared_from_this());
};
#pragma endregion
