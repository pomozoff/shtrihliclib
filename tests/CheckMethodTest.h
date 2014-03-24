
#pragma once

#include <memory>

#include "gtest/gtest.h"

#include "CheckMethod.h"
#include "ProtectKey.h"

class CheckMethodTest : public ::testing::Test {
	public:
		virtual ~CheckMethodTest(void);
	protected:
		CheckMethodTest(void);

		const feature_t feature = 3;
		protect_key_t _protect_key_hasp_sl;
};
