
#include "stdafx.h"
#include <iostream>

#include "CheckMethodMemory.h"
#include "IKeyChecker.h"

CheckMethodMemory::CheckMethodMemory(const offset_t offset, const std::vector<byte_t>& value, const CheckMethodLogin& logged_in_method) {
	m_check_method = CheckMethodType::Memory;
	m_offset = offset;
	m_value = value;
}
CheckMethodMemory::~CheckMethodMemory(void) {
}

const bool CheckMethodMemory::check(const IKeyChecker& key_checker) const {
	return false;
};
