
#include "stdafx.h"

#include "MockRealKey.h"

#pragma region Constructor Destructor
MockRealKey::MockRealKey(void) {
}
MockRealKey::~MockRealKey(void) {
}
#pragma endregion

#pragma region Protected
const bool MockRealKey::is_enabled(void) const {
	return _is_enabled;
}
void MockRealKey::set_enabled(const bool is_enabled) const {
	_is_enabled = is_enabled;
}
const bool  MockRealKey::add_logged_in_user(void) const {
	auto successful_login = _logged_in_users_amount < static_cast<int>(_max_logins_amount);
	if (successful_login) {
		_logged_in_users_amount++;
	}
	return successful_login;
}
void MockRealKey::del_logged_in_user(void) const {
	if (_logged_in_users_amount > 0) {
		_logged_in_users_amount--;
	}
}
const int MockRealKey::logged_in_users_amount(void) const {
	return _logged_in_users_amount;
}
const bool MockRealKey::is_key_nfr(void) const {
	return _is_key_nfr;
}
void MockRealKey::set_is_key_nfr(const bool value) const {
	_is_key_nfr = value;
}
const size_t MockRealKey::max_logins_amount(void) const {
	return _max_logins_amount;
}
void MockRealKey::set_max_logins_amount(const size_t value) const {
	_max_logins_amount = value;
}
#pragma endregion
