
#include "stdafx.h"

#include "ProtectKeyHaspSLTest.h"
#include "ProtectKeyHaspSL.h"

#pragma region Constructor Destructor
ProtectKeyHaspSLTest::ProtectKeyHaspSLTest() {
	_protect_key_hasp_sl = ProtectKey::create_key(KeyType::HaspSL);
}
ProtectKeyHaspSLTest::~ProtectKeyHaspSLTest() {
}
#pragma endregion Constructor Destructor

#pragma region Tests
TEST_F(ProtectKeyHaspSLTest, copy_block_to_buffer) {
	auto protect_key = ProtectKey::create_key(KeyType::HaspSL);
	//protect_key
}
#pragma endregion Tests
