
#include "stdafx.h"

#include "CheckMethodTest.h"
#include "RealKeyHaspSL.h"
#include "ProtectKeyHaspSL.h"

#pragma region Constructor Destructor
CheckMethodTest::CheckMethodTest(void) {
	auto key = std::make_shared<const RealKeyHaspSL>();
	_protect_key_hasp_sl = std::make_shared<const ProtectKeyHaspSL>(key);
}
CheckMethodTest::~CheckMethodTest(void) {
}
#pragma endregion Constructor Destructor
