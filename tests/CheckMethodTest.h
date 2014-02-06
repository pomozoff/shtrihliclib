
#pragma once

#include <memory>

#include "gtest\gtest.h"
#include "CheckMethod.h"

class CheckMethodTest : public ::testing::Test {
	public:
		CheckMethodTest();
		virtual ~CheckMethodTest();
	protected:
		std::unique_ptr<CheckMethod> m_check_method;
};
