
#include "stdafx.h"

#include "ProtectKeyTest.h"
#include "ProtectKeyHaspSL.h"
#include "LicenseBlock.h"

ProtectKeyTest::ProtectKeyTest(void) {
	_protect_key_hasp_sl = ProtectKey::create_key(KeyType::HaspSL);
}
ProtectKeyTest::~ProtectKeyTest(void) {
}

TEST_F(ProtectKeyTest, copy_block_to_buffer) {
	byte_t first_byte = 124;
	byte_t last_byte = 235;
	time_t some_time = 1392379203;
	const value_t block = LicenseBlock::block_from_string(R"(computer-user)", some_time);
	ASSERT_EQ(block[0], first_byte);
	ASSERT_EQ(block[LicenseBlock::sizeof_block - 1], last_byte);

	offset_t block_offset = LicenseBlock::sizeof_block * 4;
	value_t buffer(ProtectKeyHaspSL::ReadWriteMemorySize);
	bool successs_copy = ProtectKey::copy_block_to_buffer(block, buffer, sizeof block, 0, block_offset);
	ASSERT_TRUE(successs_copy);
	ASSERT_EQ(buffer[block_offset], first_byte);
	ASSERT_EQ(buffer[block_offset + LicenseBlock::sizeof_block - 1], last_byte);
}
