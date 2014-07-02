
#ifndef __KEYCHECKER_H__
#define __KEYCHECKER_H__

#include <vector>
#include <map>

#include "IKeyChecker.h"
#include "CheckMethod.h"

using handles_t = std::map<const check_method_login_t, const key_handle_t>;
using handles_pair_t = std::pair<const check_method_login_t, const key_handle_t>;
using check_methods_t = std::vector<const check_method_t>;

class KeyChecker : public IKeyChecker {
	public:
		virtual ~KeyChecker(void);

		const check_method_base_t create_check_method_base(void) const;
		const check_method_login_t create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key) const;
		const check_method_memory_t create_check_method_memory(const offset_t offset, const value_t& value, const check_method_login_t logged_in_method) const;

		virtual void logout(const bool forced_logout) const;

		virtual const key_handle_t get_handle(const check_method_login_t check_method) const = 0;
	protected:
		KeyChecker(void);

		mutable check_methods_t _check_methods;
		mutable handles_t _handles;
		mutable check_method_login_t _last_loggedin_method;

		virtual const bool check(void) const = 0;
		void set_max_check_number(const check_number_t check_number) const;
		void add_handle(const check_method_login_t check_method, const key_handle_t handle) const;
		const bool del_handle(const check_method_login_t check_method) const;

		/* IKeyChecker Interface */
		virtual const bool is_able_to_login(const check_method_login_t check_method) const override;
	private:
};

#endif // __KEYCHECKER_H__
