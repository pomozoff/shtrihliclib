
#ifndef __CHECKMETHODBASETEST_H__
#define __CHECKMETHODBASETEST_H__

#include "CheckMethodTest.h"

class CheckMethodBaseTest : public CheckMethodTest {
	public:
		CheckMethodBaseTest(void);
		~CheckMethodBaseTest(void);
	protected:
		check_method_base_t _check_method;
};

#endif // __CHECKMETHODBASETEST_H__
