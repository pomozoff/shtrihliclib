
#pragma once

#include <memory>

#include "gtest/gtest.h"

#include "ProtectKey.h"
#include "MockRealKeyHaspSL.h"
#include "CheckMethodMemory.h"

class CheckMethodTest : public ::testing::Test {
	public:
		virtual ~CheckMethodTest(void);
	protected:
		CheckMethodTest(void);

		const size_t _licenses_amount_null  = 0;
		const size_t _licenses_amount_one   = 1;
		const size_t _licenses_amount_two   = 2;
		const size_t _licenses_amount_three = 3;
		const feature_t _feature = 3;
		const std::wstring _session_id = L"(computer-username)";

		const protect_key_t _protect_key_hasp_sl;
};
