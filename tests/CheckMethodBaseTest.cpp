
#include "stdafx.h"
#include <memory>

#include "ProtectKey.h"
#include "CheckMethodBaseTest.h"

CheckMethodBaseTest::CheckMethodBaseTest() {
	auto protect_key = ProtectKey::create_key(KeyType::HaspSL);
	_check_method = protect_key->create_check_method_base();
}
CheckMethodBaseTest::~CheckMethodBaseTest() {
}

TEST_F(CheckMethodBaseTest, check) {
	auto protect_key = ProtectKey::create_key(KeyType::HaspSL);
	bool successful_checked = _check_method->check(protect_key);
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodBaseTest, check_method_type) {
	CheckMethodType check_method_type = _check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Base);
}
