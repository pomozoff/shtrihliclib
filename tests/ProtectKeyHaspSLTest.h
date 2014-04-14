
#pragma once

#include "gtest/gtest.h"

#include "ProtectKey.h"
#include "ProtectKeyHaspSL.h"
#include "MockRealKeyHaspSL.h"

class ProtectKeyHaspSLTest : public ::testing::Test {
	public:
		~ProtectKeyHaspSLTest(void);

		static const protect_key_t create_hasp_sl_key(const feature_t feature, const std::wstring session_id, const size_t licenses_amount);
		static const protect_key_t create_hasp_sl_key(const feature_t feature, const std::wstring session_id, const size_t licenses_amount, const check_methods_memory_t& check_methods_memory);
	protected:
		ProtectKeyHaspSLTest(void);

		const feature_t _feature = 3;
		const std::wstring _session_id = L"(computer-username)";
		const size_t _licenses_amount_two = 2;

		const protect_keys_t createKeys(void) const;
};
