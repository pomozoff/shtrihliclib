
#pragma once

#include <stdint.h>

#include "DataTypes.h"

class IProtectKey {
	public:
		virtual ~IProtectKey(void);

		virtual const bool check_license(void) const = 0;
		virtual const bool is_key_nfr(void) const = 0;
		virtual const bool is_key_base(void) const = 0;
		virtual const bool decrypt(uint8_t* buffer, const size_t length) const = 0;

		void set_decrypt_method(const check_method_login_t decrypt_method) const;
	protected:
		IProtectKey(void);

		mutable check_method_login_t _decrypt_method = nullptr;
};
