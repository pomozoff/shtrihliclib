
#pragma once

#include "ProtectKey.h"
#include "hasp/hasp_api.h"

class ProtectKeyHaspSL final : public ProtectKey {
	public:
		ProtectKeyHaspSL(void);
		~ProtectKeyHaspSL(void);

		static const size_t read_write_memory_size = 4032;

		/* ProtectKey Interface */
		virtual const value_t read_memory(const check_method_memory_t check_method) const override;

		/* IKeyChecker Interface */
		virtual const bool is_able_to_login(const check_method_login_t check_method) const override;
		virtual const bool is_same_memory(const check_method_memory_t check_method) const override;
		virtual const bool logout_key(const check_method_login_t check_method) const override;
	protected:
		KeyType _key_type = KeyType::HaspSL;
	private:
		void free_licnese(void) const;
};
