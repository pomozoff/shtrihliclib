
#ifndef __DECRYPTTEST_H__
#define __DECRYPTTEST_H__

#include "gtest/gtest.h"

#include "ProtectKey.h"

class DecryptTest : public ::testing::Test {
	public:
		DecryptTest(void);
		~DecryptTest(void);
	protected:
		protect_key_t _protect_key_hasp_sl;
};

#endif // __DECRYPTTEST_H__
