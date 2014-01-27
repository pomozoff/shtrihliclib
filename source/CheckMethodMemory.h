
#pragma once

#include "CheckMethod.h"

class CheckMethodMemory : public CheckMethod {
	public:
		~CheckMethodMemory(void);

		virtual bool check(IKeyChecker key_checker);
	protected:
		CheckMethodMemory(void);
	private:
};
