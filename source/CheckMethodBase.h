
#pragma once

#include "CheckMethod.h"

class CheckMethodBase : public CheckMethod {
	public:
		~CheckMethodBase(void);

		virtual bool check(IKeyChecker key_checker);
	protected:
		CheckMethodBase(void);
	private:
};
