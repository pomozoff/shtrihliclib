﻿
#include "stdafx.h"

#include "CheckMethodBase.h"
#include "KeyChecker.h"

CheckMethodBase::CheckMethodBase(void) :
m_check_method(CheckMethodType::Base)
{
}
CheckMethodBase::~CheckMethodBase(void) {
}

const bool CheckMethodBase::check(const std::unique_ptr<IKeyChecker> key_checker) const {
	std::shared_ptr<const CheckMethodBase> sp_this = shared_from_this();
	bool logged_in = key_checker->is_base_key_available(sp_this);
	return false;
};
