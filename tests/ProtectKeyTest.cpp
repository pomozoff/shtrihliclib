
#include "stdafx.h"

#include "ProtectKeyTest.h"
#include "ProtectKeyHaspSL.h"
#include "LicenseBlock.h"

ProtectKeyTest::ProtectKeyTest() {
	_protect_key_hasp_sl = ProtectKey::create_key(KeyType::HaspSL);
}
ProtectKeyTest::~ProtectKeyTest() {
}

TEST_F(ProtectKeyTest, copy_block_to_buffer) {
	const value_t block = LicenseBlock::create_block_as_buffer_from_string(R"(computer-user)", time(NULL));
	value_t buffer(ProtectKeyHaspSL::ReadWriteMemorySize);
	
	ProtectKey::copy_block_to_buffer(block, buffer, sizeof block, 0, LicenseBlock::sizeof_block * 4);
}
