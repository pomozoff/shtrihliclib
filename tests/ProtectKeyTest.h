
#pragma once

#include "gtest\gtest.h"
#include "ProtectKey.h"

class ProtectKeyTest : public ::testing::Test {
	public:
		ProtectKeyTest();
		~ProtectKeyTest();
	protected:
		protect_key_t _protect_key_hasp_sl;
};
