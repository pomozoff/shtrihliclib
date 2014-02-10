
#pragma once

#include "CheckMethod.h"

class CheckMethodLogin final : public CheckMethod, public std::enable_shared_from_this<CheckMethodLogin> {
	public:
		CheckMethodLogin(const feature_t feature, const bool allow_to_login_on_previous_key);
		~CheckMethodLogin(void);

		virtual const bool check(const std::shared_ptr<const IKeyChecker> key_checker) const override final;
	protected:
	private:
		// Наследование из базового класса CheckMethod
		const CheckMethodType m_check_method = CheckMethodType::Login;
	private:
		feature_t m_feature;
		bool m_allow_to_login_on_previous_key;
};
