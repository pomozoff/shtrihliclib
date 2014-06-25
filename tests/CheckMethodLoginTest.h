
#ifndef __CHECKMETHODLOGINTEST_H__
#define __CHECKMETHODLOGINTEST_H__

#include "CheckMethodTest.h"

class CheckMethodLoginTest : public CheckMethodTest {
	public:
		CheckMethodLoginTest(void);
		~CheckMethodLoginTest(void);
	protected:
		check_method_login_t _check_method;
};

#endif // __CHECKMETHODLOGINTEST_H__
