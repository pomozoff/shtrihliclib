
#ifndef __GRANULETEST_H__
#define __GRANULETEST_H__

#include "gtest/gtest.h"

#include "ProtectKey.h"

class GranuleTest : public ::testing::Test {
	public:
		GranuleTest(void);
		virtual ~GranuleTest(void);
	protected:
		const std::wstring _granule_name = L"Безлимитный кассир";
		const iprotect_key_t _iprotect_key;
	private:
		const protect_key_t create_protect_key(void) const;
};

#endif // __GRANULETEST_H__
