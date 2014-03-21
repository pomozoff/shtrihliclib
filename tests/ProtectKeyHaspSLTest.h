
#pragma once

#include "gtest/gtest.h"

#include "ProtectKey.h"

class ProtectKeyHaspSLTest : public ::testing::Test {
	public:
		ProtectKeyHaspSLTest(void);
		~ProtectKeyHaspSLTest(void);
	private:
		protect_key_t _protect_key_hasp_sl;
};
