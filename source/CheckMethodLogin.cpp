﻿
#include "stdafx.h"

#include "CheckMethodLogin.h"
#include "KeyChecker.h"

CheckMethodLogin::CheckMethodLogin(const feature_t feature, const bool allow_to_login_on_previous_key) :
_feature(feature),
_allow_to_login_on_previous_key(allow_to_login_on_previous_key)
{
}
CheckMethodLogin::~CheckMethodLogin(void) {
}

const bool CheckMethodLogin::check(const ikey_checker_t key_checker) const {
	check_method_login_t sp_this = shared_from_this();
	bool logged_in = key_checker->is_able_to_login(sp_this);
	return false;
};
