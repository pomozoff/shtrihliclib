
#pragma once

#include "CheckMethod.h"

class CheckMethodBase : public CheckMethod {
	public:
		CheckMethodBase(void);
		~CheckMethodBase(void);

		virtual const bool check(const std::unique_ptr<IKeyChecker> key_checker) const override final;
	protected:
	private:
		// Наследование из базового класса CheckMethod
		CheckMethodType m_check_method;
};
