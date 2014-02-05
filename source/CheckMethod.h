
#pragma once

#include <vector>

enum class CheckMethodType { Base, Login, Memory };

using byte_t = unsigned char;
using offset_t = unsigned long;
using feature_t = unsigned long;

class CheckMethodLogin;
class IKeyChecker;

class CheckMethod {
	public:
		static CheckMethod* create_check_method_login(const feature_t feature);
		static CheckMethod* create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key);
		static CheckMethod* create_check_method_memory(const offset_t offset, const std::vector<byte_t>& value, const CheckMethodLogin& logged_in_method);
		static CheckMethod* create_check_method_base(void);

		virtual const bool check(const IKeyChecker& key_checker) const = 0;
		virtual const CheckMethodType check_method_type(void) const final;

		virtual ~CheckMethod(void);
	protected:
		CheckMethodType m_check_method;

		CheckMethod(void);

		virtual const bool process_check_result(const bool last_check_is_success) const final;
	private:
		bool m_logout_after_check;
		bool m_is_check_method_for_NFR;
		bool m_is_check_method_for_license;

		const unsigned int m_max_check_number = 3;
		mutable unsigned int m_current_check_number;
};
