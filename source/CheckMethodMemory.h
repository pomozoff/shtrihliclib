
#pragma once

#include "CheckMethod.h"

class CheckMethodMemory : public CheckMethod {
	public:
		~CheckMethodMemory(void);

		virtual bool check(const IKeyChecker* key_checker) final;
		virtual check_method_t check_method_type(void) final;
	protected:
		CheckMethodMemory(void);
	private:
		unsigned long m_offset;
		unsigned char* m_value;
};
