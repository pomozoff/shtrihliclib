
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
void KeyChecker::logout(const bool forced_logout) const {
	for (auto iterator = _handles.begin(); iterator != _handles.end(); ) {
		auto& check_method_login = iterator->first;
		if (forced_logout || check_method_login->logout_after_check()) {
			if (logout_key(check_method_login)) {
				del_handle(iterator++->first);
				continue;
			}
		}
		++iterator;
	}
}
void KeyChecker::add_handle(const check_method_login_t check_method, const key_handle_t handle) const {
	_handles.insert(handles_pair_t(check_method, handle));
}
const bool KeyChecker::del_handle(const check_method_login_t check_method) const {
	if (check_method == _last_loggedin_method) {
		_last_loggedin_method = nullptr;
	}
	auto iterator = _handles.find(check_method);
	bool handle_found = iterator != _handles.end();
	if (handle_found) {
		_handles.erase(iterator);
	}
	return handle_found;
}
#pragma endregion

#pragma region IKeyChecker Interface
const bool KeyChecker::is_able_to_login(const check_method_login_t check_method) const {
	bool need_to_logout = !check_method->allow_to_login_on_previous_key();
	bool result = true;
	if (need_to_logout) {
		result = logout_key(check_method);
		if (result) {
			del_handle(check_method);
		}
	}
	return result;
}
#pragma endregion
