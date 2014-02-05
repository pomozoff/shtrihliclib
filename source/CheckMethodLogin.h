
#pragma once

#include "CheckMethod.h"

class CheckMethodLogin : public CheckMethod {
	public:
		CheckMethodLogin(const feature_t feature, const bool allow_to_login_on_previous_key);
		~CheckMethodLogin(void);

		virtual const bool check(const IKeyChecker& key_checker) const override final;
	protected:
		CheckMethodLogin(const feature_t feature) : CheckMethodLogin(feature, false) {};
	private:
		// Наследование из базового класса CheckMethod
		CheckMethodType m_check_method;
	private:
		feature_t m_feature;
		bool m_allow_to_login_on_previous_key;
};
