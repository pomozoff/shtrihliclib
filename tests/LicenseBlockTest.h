
#pragma once

#include "gtest\gtest.h"
#include "LicenseBlock.h"
#include "ProtectKeyHaspSL.h"

class LicenseBlockTest : public ::testing::Test {
	public:
		LicenseBlockTest();
		~LicenseBlockTest();
	private:
		value_t _key_memory;
};
