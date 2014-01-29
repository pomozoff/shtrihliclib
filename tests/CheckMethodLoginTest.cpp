
#include "stdafx.h"
#include "CheckMethodLoginTest.h"

CheckMethodLoginTest::CheckMethodLoginTest() {
	m_check_method = CheckMethod::create_check_method_login(0);
}
CheckMethodLoginTest::~CheckMethodLoginTest() {
	delete m_check_method;
}

TEST_F(CheckMethodLoginTest, check) {
	bool successful_checked = m_check_method->check(0);
	ASSERT_TRUE(successful_checked);
}

TEST_F(CheckMethodLoginTest, check_method_type) {
	check_method_t check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CHECK_METHOD_LOGIN);
}
