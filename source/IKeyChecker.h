
#ifndef __IKEYCHECKER_H__
#define __IKEYCHECKER_H__

#include "CheckMethod.h"

class IKeyChecker {
	public:
		virtual ~IKeyChecker(void);

		virtual const bool is_base_key_available(const check_method_base_t check_method) const = 0;
		virtual const bool is_able_to_login(const check_method_login_t check_method) const = 0;
		virtual const bool is_same_memory(const check_method_memory_t check_method) const = 0;
		virtual const bool logout_key(const check_method_login_t check_method) const = 0;
	protected:
		IKeyChecker(void);
	private:
};

#endif // __IKEYCHECKER_H__
