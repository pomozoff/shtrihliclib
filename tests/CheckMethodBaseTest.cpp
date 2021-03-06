
#include "stdafx.h"

#include "CheckMethodBaseTest.h"
#include "CheckMethodBase.h"

#pragma region Constructor Destructor
CheckMethodBaseTest::CheckMethodBaseTest(void) {
	_check_method = _protect_key_hasp_sl->create_check_method_base();
}
CheckMethodBaseTest::~CheckMethodBaseTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(CheckMethodBaseTest, check_method_type) {
	CheckMethodType check_method_type = _check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Base);
}
TEST_F(CheckMethodBaseTest, check) {
	auto successful_checked = _check_method->check(_protect_key_hasp_sl);
	ASSERT_TRUE(!successful_checked);
}
#pragma endregion
