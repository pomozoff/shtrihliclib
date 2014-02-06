
#include "stdafx.h"

#include "KeyChecker.h"
#include "CheckMethodBaseTest.h"

CheckMethodBaseTest::CheckMethodBaseTest() {
	auto key_checker = std::make_unique<KeyChecker>();
	m_check_method = key_checker->create_check_method_base();
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
	std::unique_ptr<CheckMethodBaseTestable> check_method = std::make_unique<CheckMethodBaseTestable>();
	bool check_is_successful = check_method->process_check_result(true);
	ASSERT_TRUE(check_is_successful);
}
