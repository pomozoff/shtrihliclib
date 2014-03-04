
#pragma once

#include "gtest\gtest.h"
#include "ProtectKey.h"

class ProtectKeyTest : public ::testing::Test {
	public:
		ProtectKeyTest(void);
		~ProtectKeyTest(void);
	private:
		protect_key_t _protect_key_hasp_sl;
};
