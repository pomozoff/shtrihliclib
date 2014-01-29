
#pragma once

#include "CheckMethod.h"

class CheckMethodMemory : public CheckMethod {
	public:
		CheckMethodMemory(const unsigned long offset, const unsigned char* value, const CheckMethodLogin* logged_in_method);
		~CheckMethodMemory(void);

		virtual bool check(const IKeyChecker* key_checker) final;
		virtual check_method_t check_method_type(void) final;
	protected:
	private:
		unsigned long m_offset;
		unsigned char* m_value;
};
