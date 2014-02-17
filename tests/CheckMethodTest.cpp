
#include "stdafx.h"

#include "CheckMethodTest.h"

CheckMethodTest::CheckMethodTest(void) {
	_protect_key_hasp_sl = ProtectKey::create_key(KeyType::HaspSL);
}
CheckMethodTest::~CheckMethodTest(void) {
}
