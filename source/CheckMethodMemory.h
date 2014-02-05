
#pragma once

#include "CheckMethod.h"

class CheckMethodMemory : public CheckMethod {
	public:
		CheckMethodMemory(const feature_t offset, const std::vector<byte_t>* value, const CheckMethodLogin* logged_in_method);
		~CheckMethodMemory(void);

		virtual bool const check(const IKeyChecker& key_checker) override final;
	protected:
	private:
		offset_t m_offset;
		std::vector<byte_t> m_value;
};
