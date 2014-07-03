
#ifndef __REALKEY_H__
#define __REALKEY_H__

template <typename T>
class RealKey {
	public:
		virtual ~RealKey(void) {};

		/* Accessors */
		inline const T last_status(void) const {
			return _last_status;
		}
	protected:
		RealKey(void) {};
		mutable T _last_status;
};

#endif // __REALKEY_H__
