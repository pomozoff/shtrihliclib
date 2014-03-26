
#include "stdafx.h"

#include "CheckMethodMemoryTest.h"
#include "CheckMethodMemory.h"
#include "CheckMethodLogin.h"

#pragma region Constructor Destructor
CheckMethodMemoryTest::CheckMethodMemoryTest(void) {
	auto check_method_login = _protect_key_hasp_sl->create_check_method_login(_feature, true);
	_check_method = _protect_key_hasp_sl->create_check_method_memory(_offset_for_constructor_test, _value_for_constructor_test, check_method_login);
}
CheckMethodMemoryTest::~CheckMethodMemoryTest(void) {
}
#pragma endregion Constructor Destructor

#pragma region Tests
TEST_F(CheckMethodMemoryTest, check_method_type) {
	CheckMethodType check_method_type = _check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Memory);
}
TEST_F(CheckMethodMemoryTest, check) {
	auto check_method_login = _check_method->logged_in_method();
	check_method_login->set_logout_after_check(false);
	check_method_login->check(_protect_key_hasp_sl);
	auto successful_checked = _check_method->check(_protect_key_hasp_sl);
	ASSERT_TRUE(successful_checked);
}
#pragma endregion Tests
