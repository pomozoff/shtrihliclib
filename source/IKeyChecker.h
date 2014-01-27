
#pragma once

#include "CheckMethod.h"
#include "CheckMethodBase.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"

class IKeyChecker {
	public:
		IKeyChecker(void);
		virtual ~IKeyChecker(void);
	private:
		bool isAbleToLogin(CheckMethodLogin *checkMethod);
		bool isSameMemory(CheckMethodMemory *checkMethod);
		bool logoutKey(CheckMethodLogin *checkMethod);
		bool isKeyAvailable(CheckMethodBase *checkMethod);
};
