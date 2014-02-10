
#pragma once

#include "CheckMethod.h"

class CheckMethodBase final : public CheckMethod, public std::enable_shared_from_this<CheckMethodBase> {
	public:
		CheckMethodBase(void);
		~CheckMethodBase(void);

		virtual const bool check(const std::shared_ptr<const IKeyChecker> key_checker) const override final;
	protected:
	private:
		// Наследование из базового класса CheckMethod
		const CheckMethodType m_check_method = CheckMethodType::Base;
};
