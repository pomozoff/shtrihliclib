
#include "stdafx.h"
#include <memory>

#include "ProtectKey.h"
#include "CheckMethodBaseTest.h"

CheckMethodBaseTest::CheckMethodBaseTest() {
	auto protect_key = std::make_unique<const ProtectKey>();
	m_check_method = protect_key->create_check_method_base();
}
CheckMethodBaseTest::~CheckMethodBaseTest() {
}

TEST_F(CheckMethodBaseTest, check) {
	auto protect_key = std::make_unique<const ProtectKey>();
	bool successful_checked = m_check_method->check(std::move(protect_key));
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodBaseTest, check_method_type) {
	CheckMethodType check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Base);
}
