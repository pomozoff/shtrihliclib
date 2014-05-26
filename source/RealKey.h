
#pragma once

#include "DataTypes.h"

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
