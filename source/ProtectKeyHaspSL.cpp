
#include "stdafx.h"

#include "ProtectKeyHaspSL.h"

ProtectKeyHaspSL::ProtectKeyHaspSL() {
}
ProtectKeyHaspSL::~ProtectKeyHaspSL() {
}

/* ProtectKey Interface */
const value_t ProtectKeyHaspSL::read_memory(const check_method_memory_t checkMethod) const {
	value_t value;
	return value;
}

/* IKeyChecker Interface */
const bool ProtectKeyHaspSL::is_able_to_login(const check_method_login_t checkMethod) const {
	return false;
}
const bool ProtectKeyHaspSL::is_same_memory(const check_method_memory_t checkMethod) const {
	return false;
}
const bool ProtectKeyHaspSL::logout_key(const check_method_login_t checkMethod) const {
	return false;
}

/* Private */
void ProtectKeyHaspSL::free_licnese(void) const {

}
