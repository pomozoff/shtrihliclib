
#pragma once

#include <memory>
#include <vector>
#include <map>

#include "IKeyChecker.h"
#include "ICheckMethodsManager.h"
#include "ICheckMethodsViewer.h"
#include "CheckMethod.h"

using handles_t = std::map<const check_method_login_t, const handle_t>;
using check_methods_t = std::vector<check_method_t>;

class KeyChecker : public IKeyChecker, public ICheckMethodsManager, public ICheckMethodsViewer {
	public:
		KeyChecker(void);
		~KeyChecker(void);

		const check_method_t create_check_method_base(void) const;
		const check_method_t create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key) const;
		const check_method_t create_check_method_memory(const offset_t offset, value_t& value, check_method_t logged_in_method) const;
	protected:
		mutable check_methods_t _check_methods;

		virtual const bool check(void) const = 0;
		virtual void set_max_check_number(check_number_t check_number) const final;
		virtual void logout(const bool forced_logout) const;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const check_method_base_t checkMethod) const override = 0;
		virtual const bool is_able_to_login(const check_method_login_t checkMethod) const override;
		virtual const bool is_same_memory(const check_method_memory_t checkMethod) const override = 0;
		virtual const bool logout_key(const check_method_login_t checkMethod) const override = 0;
	private:
		handles_t _handles;
};
