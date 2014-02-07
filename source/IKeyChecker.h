
#pragma once

#include <memory>

class CheckMethod;
class CheckMethodBase;
class CheckMethodLogin;
class CheckMethodMemory;

class IKeyChecker {
	public:
		virtual ~IKeyChecker(void);

		virtual const bool is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const = 0;
		virtual const bool is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const = 0;
		virtual const bool logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const = 0;
		virtual const bool is_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const = 0;
	protected:
		IKeyChecker(void);
	private:
};
