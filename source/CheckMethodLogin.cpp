
#include "stdafx.h"

#include "CheckMethodLogin.h"
#include "KeyChecker.h"

CheckMethodLogin::CheckMethodLogin(const feature_t feature, const bool allow_to_login_on_previous_key) :
m_feature(feature),
m_allow_to_login_on_previous_key(allow_to_login_on_previous_key)
{
}
CheckMethodLogin::~CheckMethodLogin(void) {
}

const bool CheckMethodLogin::check(const std::shared_ptr<const IKeyChecker> key_checker) const {
	std::shared_ptr<const CheckMethodLogin> sp_this = shared_from_this();
	bool logged_in = key_checker->is_able_to_login(sp_this);
	return false;
};
