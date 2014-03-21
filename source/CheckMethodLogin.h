
#pragma once

#include "CheckMethod.h"

class CheckMethodLogin final : public CheckMethod, public std::enable_shared_from_this<CheckMethodLogin> {
	public:
		CheckMethodLogin(const feature_t feature, const bool allow_to_login_on_previous_key);
		~CheckMethodLogin(void);

		/* CheckMethod Interface */
		virtual const bool check(const ikey_checker_t key_checker) const override final;

		/* Accessors */
		const feature_t feature(void) const;
		const bool allow_to_login_on_previous_key(void) const;
	protected:
	private:
		const feature_t _feature;
		const bool _allow_to_login_on_previous_key;
};
