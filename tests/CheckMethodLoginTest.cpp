
#include "stdafx.h"

#include "ProtectKey.h"
#include "CheckMethodLoginTest.h"

CheckMethodLoginTest::CheckMethodLoginTest() {
	auto protect_key = std::make_unique<const ProtectKey>();
	m_check_method = protect_key->create_check_method_login(0, false);
}
CheckMethodLoginTest::~CheckMethodLoginTest() {
}

TEST_F(CheckMethodLoginTest, check) {
	auto protect_key = std::make_unique<const ProtectKey>();
	bool successful_checked = m_check_method->check(std::move(protect_key));
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodLoginTest, check_method_type) {
	CheckMethodType check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Login);
}
