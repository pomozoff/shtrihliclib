
#pragma once

#include "CheckMethod.h"

class CheckMethodMemory : public CheckMethod {
	public:
		CheckMethodMemory(const feature_t offset, const std::vector<byte_t>& value, const CheckMethodLogin& logged_in_method);
		~CheckMethodMemory(void);

		virtual const bool check(const IKeyChecker& key_checker) const override final;
	protected:
	private:
		// Наследование из базового класса CheckMethod
		CheckMethodType m_check_method;
	private:
		offset_t m_offset;
		std::vector<byte_t> m_value;
};
