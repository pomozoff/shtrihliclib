
#include "stdafx.h"

#include "CheckMethodTest.h"

#pragma region Constructor Destructor
CheckMethodTest::CheckMethodTest(void) {
	_protect_key_hasp_sl = ProtectKey::create_key(KeyType::HaspSL);
}
CheckMethodTest::~CheckMethodTest(void) {
}
#pragma endregion Constructor Destructor
