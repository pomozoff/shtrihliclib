
#pragma once

#include "CheckMethodTest.h"
#include "CheckMethodMemory.h"

class CheckMethodMemoryTest : public CheckMethodTest {
	public:
		CheckMethodMemoryTest();
		~CheckMethodMemoryTest();
	private:
		const offset_t m_offset_for_constructor_test = 3;
		std::vector<byte_t> m_value_for_constructor_test;
};
