
#pragma once

#include "gtest\gtest.h"
#include "CheckMethodBase.h"

class CheckMethodBaseTest : public ::testing::Test {
	public:
		CheckMethodBaseTest();
		~CheckMethodBaseTest();
	protected:
		CheckMethod* m_check_method;
};
