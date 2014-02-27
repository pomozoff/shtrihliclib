
#pragma once

#include "CheckMethod.h"

class CheckMethodLogin final : public CheckMethod, public std::enable_shared_from_this<CheckMethodLogin> {
	public:
		CheckMethodLogin(const feature_t feature, const bool allow_to_login_on_previous_key);
		~CheckMethodLogin(void);

		virtual const bool check(const ikey_checker_t key_checker) const override final;
	protected:
	private:
		// Наследование из базового класса CheckMethod
		const CheckMethodType _check_method = CheckMethodType::Login;
	private:
		const feature_t _feature;
		const bool _allow_to_login_on_previous_key;
};
