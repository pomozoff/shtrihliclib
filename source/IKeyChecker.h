
#pragma once

class CheckMethod;
class CheckMethodBase;
class CheckMethodLogin;
class CheckMethodMemory;

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
