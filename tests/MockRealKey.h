
#ifndef __MOCKREALCKEY_H__
#define __MOCKREALCKEY_H__

class MockRealKey {
	public:
		MockRealKey(void);
		virtual ~MockRealKey(void);

		const bool is_enabled(void) const;
		void set_enabled(const bool is_enabled) const;
	private:
		mutable bool _is_enabled = true;
};

#endif // __MOCKREALCKEY_H__
