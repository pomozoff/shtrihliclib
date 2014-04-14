
#include "stdafx.h"

#include <algorithm>

#include "KeyChecker.h"
#include "CheckMethodBase.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"

#pragma region Constructor Destructor
KeyChecker::KeyChecker(void) {
}
KeyChecker::~KeyChecker(void) {
	_check_methods.clear();
	_handles.clear();
}
#pragma endregion

#pragma region Public
const check_method_base_t KeyChecker::create_check_method_base(void) const {
	auto check_method = std::make_shared<const CheckMethodBase>();
	_check_methods.push_back(check_method);
	return check_method;
}
const check_method_login_t KeyChecker::create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key) const {
	auto check_method = std::make_shared<const CheckMethodLogin>(feature, allow_to_login_on_previous_key);
	_check_methods.push_back(check_method);
	return check_method;
}
const check_method_memory_t KeyChecker::create_check_method_memory(const offset_t offset, const value_t& value, const check_method_login_t logged_in_method) const {
	auto check_method = std::make_shared<const CheckMethodMemory>(offset, value, logged_in_method);
	_check_methods.push_back(check_method);
	return check_method;
}
#pragma endregion

#pragma region Protected
void KeyChecker::set_max_check_number(check_number_t check_number) const {
	for (const auto& element : _check_methods) {
		element->set_max_check_number(check_number);
	}
}
void KeyChecker::logout(const bool forced_logout) const {
	for (auto iterator = _handles.begin(); iterator != _handles.end(); ) {
		auto& check_method_login = iterator->first;
		if (forced_logout || check_method_login->logout_after_check()) {
			if (logout_key(check_method_login)) {
				_handles.erase(iterator++);
				continue;
			}
		}
		++iterator;
	}
}
void KeyChecker::add_handle(const check_method_login_t check_method, const key_handle_t handle) const {
	_handles.insert(handles_pair_t(check_method, handle));
}
#pragma endregion

#pragma region IKeyChecker Interface
const bool KeyChecker::is_able_to_login(const check_method_login_t check_method) const {
	return logout_key(check_method);
}
#pragma endregion