
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
		void set_logout_after_check(const bool logout_after_check) const;
		void set_check_method_for_nfr(const bool check_method_for_nfr) const;
		void set_check_method_for_license(const bool check_method_for_license) const;
	protected:
		CheckMethodType _check_method;

		CheckMethod(const CheckMethodType check_method);
	private:
		mutable bool _logout_after_check = false;
		mutable bool _is_check_method_for_nfr = false;
		mutable bool _is_check_method_for_license = false;
};

#endif // __CHECKMETHOD_H__
