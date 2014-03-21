
#include "stdafx.h"

#include "CheckMethodMemory.h"
#include "KeyChecker.h"

#pragma region Constructor Destructor
CheckMethodMemory::CheckMethodMemory(const feature_t offset, const value_t& value, const check_method_login_t logged_in_method, const KeyMemoryType memory_type) :
CheckMethod(CheckMethodType::Memory),
_offset(offset),
_value(value),
_logged_in_method(logged_in_method),
_memory_type(memory_type)
{
}
CheckMethodMemory::CheckMethodMemory(const offset_t offset, const value_t& value, const check_method_login_t logged_in_method) :
CheckMethodMemory(offset, value, logged_in_method, KeyMemoryType::ReadOnly)
{
}
CheckMethodMemory::~CheckMethodMemory(void) {
}
#pragma endregion Constructor Destructor

#pragma region CheckMethod Interface
const bool CheckMethodMemory::check(const ikey_checker_t key_checker) const {
	check_method_memory_t sp_this = shared_from_this();
	bool logged_in = key_checker->is_same_memory(sp_this);
	return false;
};
#pragma endregion CheckMethod Interface

#pragma region Accessors
const check_method_login_t CheckMethodMemory::logged_in_method(void) const {
	return _logged_in_method;
}
const offset_t CheckMethodMemory::offset(void) const {
	return _offset;
}
const value_t& CheckMethodMemory::value(void) const {
	return _value;
}
#pragma endregion Accessors
