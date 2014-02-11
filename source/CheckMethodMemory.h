
#pragma once

#include "CheckMethod.h"

class CheckMethodMemory final : public CheckMethod, public std::enable_shared_from_this<CheckMethodMemory> {
	public:
		CheckMethodMemory(const feature_t offset, const std::vector<const byte_t>& value, const std::shared_ptr<const CheckMethod> logged_in_method);
		~CheckMethodMemory(void);

		virtual const bool check(const std::shared_ptr<const IKeyChecker> key_checker) const override final;
	protected:
	private:
		// Наследование из базового класса CheckMethod
		const CheckMethodType _check_method = CheckMethodType::Memory;
	private:
		const offset_t _offset;
		const std::vector<const byte_t> _value;
		const std::shared_ptr<const CheckMethod> _logged_in_method;
};
