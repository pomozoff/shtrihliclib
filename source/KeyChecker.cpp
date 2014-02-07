
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
std::unique_ptr<CheckMethod> KeyChecker::create_check_method_memory(const offset_t offset, std::vector<byte_t>& value, std::unique_ptr<CheckMethod> logged_in_method) const {
	std::unique_ptr<CheckMethod> check_method = std::make_unique<CheckMethodMemory>(offset, std::move(value), std::move(logged_in_method));
	return check_method;
}

const bool KeyChecker::is_base_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const {
	return false;
}
const bool KeyChecker::is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const {
	return false;
}
const bool KeyChecker::is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const {
	return false;
}
const bool KeyChecker::logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const {
	return false;
}
