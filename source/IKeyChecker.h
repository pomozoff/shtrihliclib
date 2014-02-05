
#pragma once

class CheckMethod;
class CheckMethodBase;
class CheckMethodLogin;
class CheckMethodMemory;

class IKeyChecker {
	public:
		virtual ~IKeyChecker(void);

		virtual bool is_able_to_login(const CheckMethodLogin& checkMethod) const = 0;
	protected:
		IKeyChecker(void);
	private:
		bool is_same_memory(const CheckMethodMemory& checkMethod);
		bool logout_key(const CheckMethodLogin& checkMethod);
		bool is_key_available(const CheckMethodBase& checkMethod);
};
