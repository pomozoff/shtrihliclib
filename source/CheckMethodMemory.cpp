﻿
#include "stdafx.h"

#include "CheckMethodMemory.h"
#include "KeyChecker.h"

CheckMethodMemory::CheckMethodMemory(const offset_t offset, const std::vector<const byte_t>& value, const std::shared_ptr<const CheckMethod> logged_in_method) :
m_offset(offset),
m_value(std::move(value)),
m_logged_in_method(logged_in_method)
{
}
CheckMethodMemory::~CheckMethodMemory(void) {
}

const bool CheckMethodMemory::check(const std::shared_ptr<const IKeyChecker> key_checker) const {
	std::shared_ptr<const CheckMethodMemory> sp_this = shared_from_this();
	bool logged_in = key_checker->is_same_memory(sp_this);
	return false;
};
