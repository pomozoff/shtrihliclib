
#pragma once

#include "CheckMethodTest.h"

class CheckMethodBaseTest : public CheckMethodTest {
	public:
		CheckMethodBaseTest(void);
		~CheckMethodBaseTest(void);
	protected:
		check_method_base_t _check_method;
};
