
#ifndef __CHECKMETHODMEMORYTEST_H__
#define __CHECKMETHODMEMORYTEST_H__

#include "CheckMethodTest.h"

class CheckMethodMemoryTest : public CheckMethodTest {
	public:
		CheckMethodMemoryTest(void);
		~CheckMethodMemoryTest(void);
	private:
		const offset_t _offset_for_constructor_test = 3;
		const value_t _value_for_constructor_test = value_t { 0x10, 0x00, 0x4a, 0x83 };
	protected:
		check_method_memory_t _check_method;
};

#endif // __CHECKMETHODMEMORYTEST_H__
