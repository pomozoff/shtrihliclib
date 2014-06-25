
#ifndef __CHECKMETHODBASE_H__
#define __CHECKMETHODBASE_H__

#include "CheckMethod.h"

class CheckMethodBase final : public CheckMethod, public std::enable_shared_from_this<const CheckMethodBase> {
	public:
		CheckMethodBase(void);
		~CheckMethodBase(void);

		/* CheckMethod Interface */
		virtual const bool check(const ikey_checker_t key_checker) const override final;
	protected:
};

#endif // __CHECKMETHODBASE_H__
