
#pragma once

#include "CheckMethod.h"

class CheckMethodMemory final : public CheckMethod, public std::enable_shared_from_this<CheckMethodMemory> {
	public:
		CheckMethodMemory(const feature_t offset, const std::vector<byte_t>& value, const std::shared_ptr<CheckMethod> logged_in_method);
		~CheckMethodMemory(void);

		virtual const bool check(const std::unique_ptr<IKeyChecker> key_checker) const override final;
	protected:
	private:
		// Наследование из базового класса CheckMethod
		CheckMethodType m_check_method;
	private:
		offset_t m_offset;
		std::vector<byte_t> m_value;
		std::shared_ptr<CheckMethod> m_logged_in_method;
};
