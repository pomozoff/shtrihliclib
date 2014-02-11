
#pragma once

#include <memory>

#include "gtest\gtest.h"
#include "CheckMethod.h"

class CheckMethodTest : public ::testing::Test {
	public:
		CheckMethodTest();
		virtual ~CheckMethodTest();
	protected:
		check_method_t _check_method;
};
