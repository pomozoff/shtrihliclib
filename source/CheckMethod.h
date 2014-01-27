
#pragma once

typedef enum {CHECK_METHOD_LOGIN, CHECK_METHOD_MEMORY, CHECK_METHOD_BASE} check_method_t;

class CheckMethodLogin;
class IKeyChecker;

class CheckMethod {
	public:
		static CheckMethod create_check_method_login(const unsigned long program_number);
		static CheckMethod create_check_method_login(const unsigned long program_number, const bool allow_to_login_on_previous_key);
		static CheckMethod create_check_method_memory(const unsigned long offset, const char *memory, CheckMethodLogin logged_in_method);
		static CheckMethod create_check_method_base();

		virtual bool check(IKeyChecker key_checker) = 0;

		virtual ~CheckMethod(void);
	protected:
		CheckMethod(void);

		virtual check_method_t check_method_type() final = 0;
		virtual bool process_check_result(bool last_check_is_success) final;
	private:
		check_method_t m_check_method;

		bool m_logout_after_check;
		bool m_is_check_method_for_NFR;
		bool m_is_check_method_for_license;

		unsigned int m_check_count_before_error;
		unsigned int m_checks_count;
};
