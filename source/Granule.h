
#pragma once

#include "KeyChecker.h"
#include "ProtectKey.h"

class Granule final : public KeyChecker, public std::enable_shared_from_this<const Granule> {
	public:
		Granule(const std::string id, const protect_key_t protect_key);
		~Granule(void);

		/* KeyChecker Interface */
		virtual const bool check(void) const override final;

		/* Properties */
		void set_granule_nfr_date(bool is_granule_nfr_date);
		const bool is_granule_nfr_date(void) const;
	protected:
		/* KeyChecker Interface */
		virtual void logout(const bool forced_logout) const override final;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const check_method_base_t checkMethod) const override;
		virtual const bool is_able_to_login(const check_method_login_t checkMethod) const override;
		virtual const bool is_same_memory(const check_method_memory_t checkMethod) const override;
		virtual const bool logout_key(const check_method_login_t checkMethod) const override;
	private:
		const std::string _id;
		const protect_key_t _protect_key;
		bool _is_granule_nfr_date = false;
		bool _is_present = false;
		bool _read_memory_to_value = false;
		mutable value_t _value;
};
