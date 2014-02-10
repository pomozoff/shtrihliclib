
#include "stdafx.h"

#include "ProtectKey.h"
#include "CheckMethodMemoryTest.h"

CheckMethodMemoryTest::CheckMethodMemoryTest() {
	byte_t tmp[] = { 0x10, 0xfe, 0x4a, 0x83 };
	std::vector<byte_t> value_for_constructor_test { *tmp };
	
	auto protect_key = std::make_unique<ProtectKey>();
	auto check_method_login = protect_key->create_check_method_login(15, true);
	
	m_check_method = protect_key->create_check_method_memory(m_offset_for_constructor_test, std::move(value_for_constructor_test), check_method_login);
}
CheckMethodMemoryTest::~CheckMethodMemoryTest() {
}

TEST_F(CheckMethodMemoryTest, check) {
	auto protect_key = std::make_unique<ProtectKey>();
	bool successful_checked = m_check_method->check(std::move(protect_key));
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodMemoryTest, check_method_type) {
	CheckMethodType check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Memory);
}
