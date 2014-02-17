
#pragma once

#include "CheckMethodTest.h"

class CheckMethodMemoryTest : public CheckMethodTest {
	public:
		CheckMethodMemoryTest(void);
		~CheckMethodMemoryTest(void);
	private:
		const offset_t _offset_for_constructor_test = 3;
};
