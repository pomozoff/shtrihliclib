
#pragma once

#include "CheckMethod.h"

class CheckMethodLogin : public CheckMethod {
	public:
		CheckMethodLogin(const unsigned long feature, const bool allow_to_login_on_previous_key);
		~CheckMethodLogin(void);

		virtual bool check(const IKeyChecker* key_checker) final;
		virtual check_method_t check_method_type(void) final;
	protected:
		CheckMethodLogin(const unsigned long feature);
	private:
		unsigned long m_feature;
		bool m_allow_to_login_on_previous_key;
};
