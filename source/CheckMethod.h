
#pragma once

#include "DataTypes.h"

enum class CheckMethodType { Base, Login, Memory };

class CheckMethod {
	public:
		virtual ~CheckMethod(void);

		virtual const bool check(const ikey_checker_t key_checker) const = 0;
		const CheckMethodType check_method_type(void) const;

		/* Properties */
		const bool logout_after_check(void) const;
		const bool is_check_method_for_nfr(void) const;
		const bool is_check_method_for_license(void) const;
		void set_max_check_number(check_number_t check_number) const;
	protected:
		CheckMethodType _check_method;

		CheckMethod(void);

		const bool process_check_result(const bool last_check_is_success) const;
	private:
		bool _logout_after_check = false;
		bool _is_check_method_for_nfr = false;
		bool _is_check_method_for_license = false;

		mutable check_number_t _max_check_number = 1;
		mutable check_number_t _current_check_number = 0;
};
