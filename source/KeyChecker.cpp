
#include "stdafx.h"

#include "KeyChecker.h"
#include "CheckMethodBase.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"

KeyChecker::KeyChecker(void){
}
KeyChecker::~KeyChecker(void){
}

std::unique_ptr<CheckMethod> KeyChecker::create_check_method_base(void) const {
	std::unique_ptr<CheckMethod> check_method = std::make_unique<CheckMethodBase>();
	m_check_methods.push_back(std::move(check_method));
	return check_method;
}
std::unique_ptr<CheckMethod> KeyChecker::create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key) const {
	std::unique_ptr<CheckMethod> check_method = std::make_unique<CheckMethodLogin>(feature, allow_to_login_on_previous_key);
	return check_method;
}
std::unique_ptr<CheckMethod> KeyChecker::create_check_method_memory(const offset_t offset, const std::vector<byte_t>& value, const std::unique_ptr<CheckMethod>& logged_in_method) const {
	std::unique_ptr<CheckMethod> check_method = std::make_unique<CheckMethodMemory>(offset, value, logged_in_method);
	return check_method;
}

const bool KeyChecker::is_able_to_login(const CheckMethodLogin& checkMethod) const {
	return false;
}
const bool KeyChecker::is_same_memory(const CheckMethodMemory& checkMethod) const {
	return false;
}
const bool KeyChecker::logout_key(const CheckMethodLogin& checkMethod) const {
	return false;
}
const bool KeyChecker::is_key_available(const CheckMethodBase& checkMethod) const {
	return false;
}
