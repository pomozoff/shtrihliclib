
#ifndef __MOCKREALCKEY_H__
#define __MOCKREALCKEY_H__

class MockRealKey {
	public:
		MockRealKey(void);
		virtual ~MockRealKey(void);

		const bool is_enabled(void) const;
		void set_enabled(const bool is_enabled) const;
		const int logged_in_users_amount(void) const;

		const size_t max_logins_amount(void) const;
		void set_max_logins_amount(const size_t value) const;

		const bool is_key_nfr(void) const;
		void set_is_key_nfr(const bool value) const;
	protected:
		const bool add_logged_in_user(void) const;
		void del_logged_in_user(void) const;
	private:
		mutable bool _is_enabled = true;
		mutable int _logged_in_users_amount = 0;
		mutable bool _is_key_nfr = false;
		mutable size_t _max_logins_amount = 1;
};

#endif // __MOCKREALCKEY_H__
