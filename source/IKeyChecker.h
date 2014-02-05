
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
		bool is_same_memory(CheckMethodMemory* checkMethod);
		bool logout_key(CheckMethodLogin* checkMethod);
		bool is_key_available(CheckMethodBase* checkMethod);
};
