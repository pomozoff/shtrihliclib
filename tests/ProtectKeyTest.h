
#ifndef __PROTECTKEYTEST_H__
#define __PROTECTKEYTEST_H__

#include "gtest/gtest.h"

#include "ProtectKey.h"

class ProtectKeyTest : public ::testing::Test {
	public:
		ProtectKeyTest(void);
		~ProtectKeyTest(void);
	protected:
		protect_key_t _protect_key_hasp_sl;

		void printBuffer(const std::string prefix, const value_t& buffer, const offset_t offset, const size_t size) const;
};

#endif // __PROTECTKEYTEST_H__
