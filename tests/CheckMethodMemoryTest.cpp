
#include "stdafx.h"
#include "CheckMethodMemoryTest.h"

CheckMethodMemoryTest::CheckMethodMemoryTest() {
	m_check_method = CheckMethod::create_check_method_memory(0, 0, 0);
}
CheckMethodMemoryTest::~CheckMethodMemoryTest() {
	delete m_check_method;
}

TEST_F(CheckMethodMemoryTest, check) {
	bool successful_checked = m_check_method->check(0);
	ASSERT_TRUE(successful_checked);
}

TEST_F(CheckMethodMemoryTest, check_method_type) {
	check_method_t check_method_type = m_check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CHECK_METHOD_MEMORY);
}
