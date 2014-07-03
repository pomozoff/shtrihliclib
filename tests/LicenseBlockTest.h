
#ifndef __LICENSEBLOCKTEST_H__
#define __LICENSEBLOCKTEST_H__

#include "gtest/gtest.h"

#include "ProtectKey.h"
#include "LicenseBlock.h"

class LicenseBlockTest : public ::testing::Test {
	public:
		LicenseBlockTest(void);
		~LicenseBlockTest(void);
	private:
		value_t _key_memory;
		protect_key_t _protect_key_hasp_sl;

		void printBuffer(const std::string prefix, const value_t& buffer, const offset_t offset, const size_t size) const;
};

#endif // __LICENSEBLOCKTEST_H__
