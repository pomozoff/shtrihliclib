
#include "stdafx.h"

#include "KeyChecker.h"
#include "CheckMethodLoginTest.h"

CheckMethodLoginTest::CheckMethodLoginTest() {
	m_check_method = CheckMethod::create_check_method_login(0);
}
CheckMethodLoginTest::~CheckMethodLoginTest() {
}

TEST_F(CheckMethodLoginTest, check) {
	KeyChecker keyChecker;
	bool successful_checked = m_check_method->check(keyChecker);
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodLoginTest, check_method_type) {
	check_method_t check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CHECK_METHOD_LOGIN);
}
