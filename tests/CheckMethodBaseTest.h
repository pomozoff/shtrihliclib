
#pragma once

#include "CheckMethodTest.h"
#include "CheckMethodBase.h"

class CheckMethodBaseTestable : public CheckMethodBase {
	public:
		using CheckMethodBase::process_check_result;
	private:
		using CheckMethodBase::check;
		using CheckMethodBase::check_method_type;
};

class CheckMethodBaseTest : public CheckMethodTest {
	public:
		CheckMethodBaseTest();
		~CheckMethodBaseTest();
};
