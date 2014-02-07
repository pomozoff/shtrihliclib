
#include "stdafx.h"

#include "KeyChecker.h"
#include "CheckMethodMemoryTest.h"

CheckMethodMemoryTest::CheckMethodMemoryTest() {
	byte_t tmp[] = { 0x10, 0xfe, 0x4a, 0x83 };
	std::vector<byte_t> value_for_constructor_test { *tmp };
	
	auto key_checker = std::make_unique<KeyChecker>();
	auto check_method_login = key_checker->create_check_method_login(15, true);
	
	m_check_method = key_checker->create_check_method_memory(m_offset_for_constructor_test, std::move(value_for_constructor_test), std::move(check_method_login));
}
CheckMethodMemoryTest::~CheckMethodMemoryTest() {
}

TEST_F(CheckMethodMemoryTest, check) {
	auto key_checker = std::make_unique<KeyChecker>();
	bool successful_checked = m_check_method->check(std::move(key_checker));
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodMemoryTest, check_method_type) {
	CheckMethodType check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Memory);
}
