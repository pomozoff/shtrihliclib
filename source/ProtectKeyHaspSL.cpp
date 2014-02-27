
#include "stdafx.h"

#include "ProtectKeyHaspSL.h"

ProtectKeyHaspSL::ProtectKeyHaspSL(void) {
}
ProtectKeyHaspSL::~ProtectKeyHaspSL(void) {
}

/* ProtectKey Interface */
const value_t ProtectKeyHaspSL::read_memory(const check_method_memory_t check_method) const {
	value_t value;
	return value;
}

/* IKeyChecker Interface */
const bool ProtectKeyHaspSL::is_able_to_login(const check_method_login_t check_method) const {
	return false;
}
const bool ProtectKeyHaspSL::is_same_memory(const check_method_memory_t check_method) const {
	return false;
}
const bool ProtectKeyHaspSL::logout_key(const check_method_login_t check_method) const {
	return false;
}

/* Private */
void ProtectKeyHaspSL::free_licnese(void) const {

}
