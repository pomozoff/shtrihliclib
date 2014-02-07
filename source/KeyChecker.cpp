
#include "stdafx.h"

#include "KeyChecker.h"
#include "CheckMethodBase.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"

KeyChecker::KeyChecker(void) {
}
KeyChecker::~KeyChecker(void) {
	m_check_methods.clear();
	m_handles.clear();
}

std::shared_ptr<CheckMethod> KeyChecker::create_check_method_base(void) const {
	std::shared_ptr<CheckMethod> check_method = std::make_shared<CheckMethodBase>();
	m_check_methods.push_back(check_method);
	return check_method;
}
std::shared_ptr<CheckMethod> KeyChecker::create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key) const {
	std::shared_ptr<CheckMethod> check_method = std::make_shared<CheckMethodLogin>(feature, allow_to_login_on_previous_key);
	m_check_methods.push_back(check_method);
	return check_method;
}
std::shared_ptr<CheckMethod> KeyChecker::create_check_method_memory(const offset_t offset, std::vector<byte_t>& value, std::shared_ptr<CheckMethod> logged_in_method) const {
	std::shared_ptr<CheckMethod> check_method = std::make_shared<CheckMethodMemory>(offset, std::move(value), logged_in_method);
	m_check_methods.push_back(check_method);
	return check_method;
}

const bool KeyChecker::is_base_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const {
	return false;
}
const bool KeyChecker::is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const {
	return logout_key(checkMethod);
}
const bool KeyChecker::is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const {
	return false;
}
const bool KeyChecker::logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const {
	return false;
}

void KeyChecker::set_max_check_number(check_number_t check_number) const {
	for (const auto& element : m_check_methods) {
		element->set_max_check_number(check_number);
	}
}
