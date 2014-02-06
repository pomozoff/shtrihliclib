
#include "stdafx.h"

#include "CheckMethodLogin.h"
#include "KeyChecker.h"

CheckMethodLogin::CheckMethodLogin(const feature_t feature, const bool allow_to_login_on_previous_key) :
m_check_method(CheckMethodType::Login),
m_feature(feature),
m_allow_to_login_on_previous_key(allow_to_login_on_previous_key)
{
}
CheckMethodLogin::~CheckMethodLogin(void) {
}

const bool CheckMethodLogin::check(const IKeyChecker& key_checker) const {
	bool logged_in = key_checker.is_able_to_login(*this);
	return false;
};
