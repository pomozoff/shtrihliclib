
#pragma once

#include <vector>
#include <memory>

enum class CheckMethodType { Base, Login, Memory };

using byte_t    = uint8_t;
using offset_t  = uint32_t;
using feature_t = uint32_t;
using handle_t  = uint32_t;

using check_number_t = unsigned int;

class IKeyChecker;
class CheckMethod;
class CheckMethodBase;
class CheckMethodLogin;
class CheckMethodMemory;

using value_t = std::vector<const byte_t>;
using ikey_checker_t = std::shared_ptr<const IKeyChecker>;
using check_method_t = std::shared_ptr<const CheckMethod>;
using check_method_base_t = std::shared_ptr<const CheckMethodBase>;
using check_method_login_t = std::shared_ptr<const CheckMethodLogin>;
using check_method_memory_t = std::shared_ptr<const CheckMethodMemory>;

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
