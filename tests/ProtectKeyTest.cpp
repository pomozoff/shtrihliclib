
#include "stdafx.h"

#include "ProtectKeyTest.h"
#include "ProtectKeyHaspSL.h"
#include "LicenseBlock.h"
#include "Platform.h"

#pragma region Constructor Destructor
ProtectKeyTest::ProtectKeyTest(void) {
	_protect_key_hasp_sl = ProtectKey::create_key(KeyType::HaspSL, Platform::platform());
}
ProtectKeyTest::~ProtectKeyTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(ProtectKeyTest, copy_block_to_buffer) {
	byte_t first_byte = 135;
	byte_t last_byte = 215;
	time_t some_time = 1392379203;
	
	auto id = L"(computer-user)";
	const value_t block = LicenseBlock::block_from_string(id, some_time);

	ASSERT_EQ(block[0], first_byte);
	ASSERT_EQ(block[LicenseBlock::sizeof_block - 1], last_byte);

	offset_t block_offset = LicenseBlock::sizeof_block * 4;
	value_t buffer(ProtectKeyHaspSL::read_write_memory_size);
	bool successs_copy = ProtectKey::copy_block_to_buffer(block, buffer, sizeof block, 0, block_offset);

	ASSERT_TRUE(successs_copy);
	ASSERT_EQ(buffer[block_offset], first_byte);
	ASSERT_EQ(buffer[block_offset + LicenseBlock::sizeof_block - 1], last_byte);

#pragma region Private
void ProtectKeyTest::printBuffer(const std::string prefix, const value_t& buffer, const offset_t offset, const size_t size) const {
	std::cout << "Start of block offset is: " << offset << std::endl;
	std::cout << "End   of block offset is: " << offset + size - 1 << std::endl;
	for (size_t i = 0; i < size; i++) {
		std::cout << prefix << "buffer[" << offset + i << "] = " << (int)buffer[offset + i] << std::endl;
	}
}
#pragma endregion
