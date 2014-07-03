
#include "stdafx.h"

#include "CheckMethodTest.h"
#include "ProtectKeyHaspSLTest.h"

#pragma region Constructor Destructor
CheckMethodTest::CheckMethodTest(void) :
_protect_key_hasp_sl(ProtectKeyHaspSLTest::create_key(_feature, _session_id, _licenses_amount_one))
{
}
CheckMethodTest::~CheckMethodTest(void) {
}
#pragma endregion
