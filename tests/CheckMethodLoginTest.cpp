
#include "stdafx.h"

#include "CheckMethodLoginTest.h"
#include "CheckMethodLogin.h"
#include "ProtectKeyHaspSL.h"

#pragma region Constructor Destructor
CheckMethodLoginTest::CheckMethodLoginTest(void) {
	_check_method = _protect_key_hasp_sl->create_check_method_login(_feature, false);
}
CheckMethodLoginTest::~CheckMethodLoginTest(void) {
}
#pragma endregion Constructor Destructor

#pragma region Tests
TEST_F(CheckMethodLoginTest, check_method_type) {
	CheckMethodType check_method_type = _check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Login);
}
TEST_F(CheckMethodLoginTest, check) {
	auto successful_checked = _check_method->check(_protect_key_hasp_sl);
	ASSERT_TRUE(successful_checked);
}
}
#pragma endregion Tests
