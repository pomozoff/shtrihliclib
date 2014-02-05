
#include "stdafx.h"

#include "KeyChecker.h"
#include "CheckMethodMemoryTest.h"

CheckMethodMemoryTest::CheckMethodMemoryTest() {
	byte_t tmp[] = { 0x10, 0xfe, 0x4a, 0x83 };
	m_value_for_constructor_test.clear();
	m_value_for_constructor_test.insert(m_value_for_constructor_test.end(), *tmp);
	
	CheckMethodLogin *check_method_login = (CheckMethodLogin *)CheckMethod::create_check_method_login(15, true);
	
	m_check_method = CheckMethod::create_check_method_memory(m_offset_for_constructor_test, m_value_for_constructor_test, *check_method_login);
}
CheckMethodMemoryTest::~CheckMethodMemoryTest() {
}

TEST_F(CheckMethodMemoryTest, check) {
	KeyChecker keyChecker;
	bool successful_checked = m_check_method->check(keyChecker);
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodMemoryTest, check_method_type) {
	CheckMethodType check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Memory);
}
