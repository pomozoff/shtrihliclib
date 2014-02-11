
#include "stdafx.h"

#include "ProtectKey.h"
#include "CheckMethodLoginTest.h"

CheckMethodLoginTest::CheckMethodLoginTest() {
	auto protect_key = ProtectKey::create_key(KeyType::HaspSL);
	_check_method = protect_key->create_check_method_login(0, false);
}
CheckMethodLoginTest::~CheckMethodLoginTest() {
}

TEST_F(CheckMethodLoginTest, check) {
	auto protect_key = ProtectKey::create_key(KeyType::HaspSL);
	bool successful_checked = _check_method->check(protect_key);
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodLoginTest, check_method_type) {
	CheckMethodType check_method_type = _check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Login);
}
