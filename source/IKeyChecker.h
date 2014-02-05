
#pragma once

class CheckMethod;
class CheckMethodBase;
class CheckMethodLogin;
class CheckMethodMemory;

class IKeyChecker {
	public:
		virtual ~IKeyChecker(void);

		virtual bool is_able_to_login(CheckMethodLogin* checkMethod) const = 0;
	protected:
		IKeyChecker(void);
	private:
		bool isSameMemory(CheckMethodMemory* checkMethod);
		bool logoutKey(CheckMethodLogin* checkMethod);
		bool isKeyAvailable(CheckMethodBase* checkMethod);
};
