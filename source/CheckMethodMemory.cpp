
#include "stdafx.h"

#include "CheckMethodMemory.h"
#include "KeyChecker.h"

CheckMethodMemory::CheckMethodMemory(const offset_t offset, const std::vector<byte_t>& value, const std::unique_ptr<CheckMethod> logged_in_method) :
m_check_method(CheckMethodType::Memory),
m_offset(offset),
m_value(std::move(value))
{
}
CheckMethodMemory::~CheckMethodMemory(void) {
}

const bool CheckMethodMemory::check(const std::unique_ptr<IKeyChecker> key_checker) const {
	return false;
};
