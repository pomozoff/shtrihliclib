
#include "stdafx.h"

#include "CheckMethodMemoryTest.h"

CheckMethodMemoryTest::CheckMethodMemoryTest(void) {
	byte_t tmp[] = { 0x10, 0xfe, 0x4a, 0x83 };
	value_t value_for_constructor_test { *tmp };
	auto check_method_login = _protect_key_hasp_sl->create_check_method_login(15, true);
	
	_check_method = _protect_key_hasp_sl->create_check_method_memory(_offset_for_constructor_test, value_for_constructor_test, check_method_login);
}
CheckMethodMemoryTest::~CheckMethodMemoryTest(void) {
}

TEST_F(CheckMethodMemoryTest, check) {
	bool successful_checked = _check_method->check(_protect_key_hasp_sl);
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodMemoryTest, check_method_type) {
	CheckMethodType check_method_type = _check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Memory);
}
