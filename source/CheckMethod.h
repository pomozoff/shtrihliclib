
#pragma once

#include <vector>
#include <memory>

enum class CheckMethodType { Base, Login, Memory };

using byte_t    = unsigned char;
using offset_t  = unsigned long;
using feature_t = unsigned long;
using handle_t  = unsigned long;

using check_number_t = unsigned int;

class CheckMethodLogin;
class IKeyChecker;

class CheckMethod {
	public:
		virtual const bool check(const std::unique_ptr<IKeyChecker> key_checker) const = 0;
		virtual const CheckMethodType check_method_type(void) const final;
		virtual void set_max_check_number(check_number_t check_number) const final;

		virtual ~CheckMethod(void);
	protected:
		CheckMethodType m_check_method;

		CheckMethod(void);

		virtual const bool process_check_result(const bool last_check_is_success) const final;
	private:
		bool m_logout_after_check;
		bool m_is_check_method_for_NFR;
		bool m_is_check_method_for_license;

		mutable check_number_t m_max_check_number = 3;
		mutable check_number_t m_current_check_number;
};
