
#include "stdafx.h"

#include "KeyChecker.h"
#include "CheckMethodLoginTest.h"

CheckMethodLoginTest::CheckMethodLoginTest() {
	auto key_checker = std::make_unique<KeyChecker>();
	m_check_method = key_checker->create_check_method_login(0, false);
}
CheckMethodLoginTest::~CheckMethodLoginTest() {
}

TEST_F(CheckMethodLoginTest, check) {
	KeyChecker keyChecker;
	bool successful_checked = m_check_method->check(keyChecker);
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodLoginTest, check_method_type) {
	CheckMethodType check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Login);
}
