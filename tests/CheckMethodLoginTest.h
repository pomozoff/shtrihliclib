
#pragma once

#include "gtest\gtest.h"
#include "CheckMethodLogin.h"

class CheckMethodLoginTest : public ::testing::Test {
	public:
		CheckMethodLoginTest();
		~CheckMethodLoginTest();
	protected:
		CheckMethod* m_check_method;
};
