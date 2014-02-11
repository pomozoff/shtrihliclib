
#pragma once

#include "ProtectKey.h"

class ProtectKeyHaspSL final : public ProtectKey {
	public:
		ProtectKeyHaspSL();
		~ProtectKeyHaspSL();

		/* ProtectKey Interface */
		virtual const value_t read_memory(const check_method_memory_t checkMethod) const override;

		/* IKeyChecker Interface */
		virtual const bool is_able_to_login(const check_method_login_t checkMethod) const override;
		virtual const bool is_same_memory(const check_method_memory_t checkMethod) const override;
		virtual const bool logout_key(const check_method_login_t checkMethod) const override;
	protected:
		KeyType _key_type = KeyType::HaspSL;
	private:
		void free_licnese(void) const;
};
