
#include "stdafx.h"

#include "CheckMethodMemory.h"
#include "KeyChecker.h"

CheckMethodMemory::CheckMethodMemory(const offset_t offset, const value_t& value, const check_method_login_t logged_in_method) :
_offset(offset),
_value(std::move(value)),
_logged_in_method(logged_in_method)
{
}
CheckMethodMemory::~CheckMethodMemory(void) {
}

const bool CheckMethodMemory::check(const ikey_checker_t key_checker) const {
	check_method_memory_t sp_this = shared_from_this();
	bool logged_in = key_checker->is_same_memory(sp_this);
	return false;
};
