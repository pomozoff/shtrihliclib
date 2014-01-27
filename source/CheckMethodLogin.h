
#pragma once

#include "CheckMethod.h"

class CheckMethodLogin : public CheckMethod {
	public:
		~CheckMethodLogin(void);

		virtual bool check(IKeyChecker key_checker);
	protected:
		CheckMethodLogin(void);
	private:
};
