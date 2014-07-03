
#ifndef __CHECKMETHOD_H__
#define __CHECKMETHOD_H__

enum class CheckMethodType { Base, Login, Memory };

class CheckMethod {
	public:
		virtual ~CheckMethod(void);

		virtual const bool check(const ikey_checker_t key_checker) const = 0;
		const CheckMethodType check_method_type(void) const;

		/* Accessors */
		const bool logout_after_check(void) const;
		const bool is_check_method_for_nfr(void) const;
		const bool is_check_method_for_license(void) const;
		const check_number_t max_check_number(void) const;
		void set_logout_after_check(const bool logout_after_check) const;
		void set_max_check_number(const check_number_t check_number) const;
		void set_current_check_number(const check_number_t check_number) const;
		void set_check_method_for_nfr(const bool check_method_for_nfr) const;
		void set_check_method_for_license(const bool check_method_for_license) const;
	protected:
		CheckMethodType _check_method;

		CheckMethod(const CheckMethodType check_method);

		const bool process_check_result(const bool last_check_is_success) const;
	private:
		mutable bool _logout_after_check = false;
		mutable bool _is_check_method_for_nfr = false;
		mutable bool _is_check_method_for_license = false;

		mutable check_number_t _max_check_number = 1;
		mutable check_number_t _current_check_number = 0;
};

#endif // __CHECKMETHOD_H__
