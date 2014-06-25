
#ifndef __LICENSEBLOCKTEST_H__
#define __LICENSEBLOCKTEST_H__

#include "gtest/gtest.h"

#include "LicenseBlock.h"

class LicenseBlockTest : public ::testing::Test {
	public:
		LicenseBlockTest(void);
		~LicenseBlockTest(void);
	private:
		value_t _key_memory;
};

#endif // __LICENSEBLOCKTEST_H__
