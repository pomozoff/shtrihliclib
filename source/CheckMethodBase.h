
#pragma once

#include "CheckMethod.h"

class CheckMethodBase : public CheckMethod {
	public:
		CheckMethodBase(void);
		~CheckMethodBase(void);

		virtual const bool check(const IKeyChecker& key_checker) const override final;
	protected:
	private:
};
