
#pragma once

#include "gtest\gtest.h"
#include "CheckMethodMemory.h"

class CheckMethodMemoryTest : public ::testing::Test {
	public:
		CheckMethodMemoryTest();
		~CheckMethodMemoryTest();
	protected:
		CheckMethod* m_check_method;
};
