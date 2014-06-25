
#ifndef __GRANULE_H__
#define __GRANULE_H__

#include "KeyChecker.h"
#include "ProtectKey.h"

class Granule final : public KeyChecker, public std::enable_shared_from_this<const Granule> {
	public:
		Granule(const std::wstring id, const protect_key_weak_t protect_key);
		~Granule(void);

		/* KeyChecker Interface */
		virtual const bool check(void) const override final;

		/* Accessors */
		void set_granule_nfr_date(const bool is_granule_nfr_date) const;
		const bool is_granule_nfr_date(void) const;
		void set_read_memory_to_value(const bool read_memory_to_value) const;
		const bool read_memory_to_value(void) const;
	protected:
		/* KeyChecker Interface */
		virtual void logout(const bool forced_logout) const override final;
		virtual const key_handle_t get_handle(const check_method_login_t check_method) const override final;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const check_method_base_t check_method) const override final;
		virtual const bool is_able_to_login(const check_method_login_t check_method) const override final;
		virtual const bool is_same_memory(const check_method_memory_t check_method) const override final;
		virtual const bool logout_key(const check_method_login_t check_method) const override final;
	private:
		Granule& operator=(const Granule &tmp);
		
		const std::wstring _id;
		const protect_key_weak_t _protect_weak_key;

		bool _is_present = false;
		mutable bool _is_granule_nfr_date = false;
		mutable bool _read_memory_to_value = false;

		mutable value_t _value;

		const time_t make_unix_time_from_old_format(const value_t value) const;
};

#endif // __GRANULE_H__
