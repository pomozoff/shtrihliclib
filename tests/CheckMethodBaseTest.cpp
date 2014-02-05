
#include "stdafx.h"

#include "KeyChecker.h"
#include "CheckMethodBaseTest.h"

CheckMethodBaseTest::CheckMethodBaseTest() {
	m_check_method = CheckMethod::create_check_method_base();
}
CheckMethodBaseTest::~CheckMethodBaseTest() {
}

TEST_F(CheckMethodBaseTest, check) {
	KeyChecker keyChecker;
	bool successful_checked = m_check_method->check(keyChecker);
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodBaseTest, check_method_type) {
	CheckMethodType check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Base);
}
TEST_F(CheckMethodBaseTest, process_check_result) {
	CheckMethodBaseTestable* check_method = new CheckMethodBaseTestable();
	bool check_is_successful = check_method->process_check_result(true);
	ASSERT_TRUE(check_is_successful);
	delete check_method;
}
