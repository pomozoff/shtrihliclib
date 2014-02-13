
#pragma once

#include <memory>

#include "gtest\gtest.h"
#include "CheckMethod.h"
#include "ProtectKey.h"

class CheckMethodTest : public ::testing::Test {
	public:
		CheckMethodTest();
		virtual ~CheckMethodTest();
	protected:
		protect_key_t _protect_key_hasp_sl;
		check_method_t _check_method;
};
