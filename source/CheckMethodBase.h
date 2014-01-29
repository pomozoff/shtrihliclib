
#pragma once

#include "CheckMethod.h"

class CheckMethodBase : public CheckMethod {
	public:
		CheckMethodBase(void);
		~CheckMethodBase(void);

		virtual bool check(const IKeyChecker* key_checker) final;
		virtual check_method_t check_method_type(void) final;
	protected:
	private:
};
