
#include "stdafx.h"

#include "CheckMethodLogin.h"
#include "KeyChecker.h"

#pragma region Constructor Destructor
CheckMethodLogin::CheckMethodLogin(const feature_t feature, const bool allow_to_login_on_previous_key) :
CheckMethod(CheckMethodType::Login),
_feature(feature),
_allow_to_login_on_previous_key(allow_to_login_on_previous_key)
{
}
CheckMethodLogin::~CheckMethodLogin(void) {
}
#pragma endregion

#pragma region CheckMethod Interface
const bool CheckMethodLogin::check(const ikey_checker_t key_checker) const {
	auto is_logged_in = key_checker->is_able_to_login(shared_from_this());
	if (is_logged_in && logout_after_check()) {
		key_checker->logout_key(shared_from_this());
	}
	return is_logged_in;
};
#pragma endregion

#pragma region Accessors
const feature_t CheckMethodLogin::feature(void) const {
	return _feature;
}
const bool CheckMethodLogin::allow_to_login_on_previous_key(void) const {
	return _allow_to_login_on_previous_key;
}
#pragma endregion
