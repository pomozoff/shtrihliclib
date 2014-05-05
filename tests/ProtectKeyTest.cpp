
#include "stdafx.h"

#include <openssl/aes.h>
#include <openssl/rand.h>

#include "ProtectKeyTest.h"
#include "ProtectKeyHaspSL.h"
#include "LicenseBlock.h"
#include "Platform.h"

static const uint16_t AES_key_length = 256;

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
	ASSERT_EQ(block.size(), LicenseBlock::sizeof_block);

	ASSERT_EQ(block[0], first_byte);
	ASSERT_EQ(block[LicenseBlock::sizeof_block - 1], last_byte);

	value_t buffer(ProtectKeyHaspSL::read_write_memory_size);
	ASSERT_EQ(buffer.size(), ProtectKeyHaspSL::read_write_memory_size);

	offset_t block_offset = LicenseBlock::sizeof_block * 4;
	bool successs_copy = ProtectKey::copy_block_to_buffer(block, buffer, LicenseBlock::sizeof_block, 0, block_offset);

	ASSERT_TRUE(successs_copy);
	ASSERT_EQ(block.size(), LicenseBlock::sizeof_block);
	ASSERT_EQ(buffer.size(), ProtectKeyHaspSL::read_write_memory_size);

	//printBuffer(R"(Block after - )", block, 0, LicenseBlock::sizeof_block);
	//printBuffer(R"(Buffer - )", buffer, block_offset, LicenseBlock::sizeof_block);

	ASSERT_EQ(buffer[block_offset], first_byte);
	offset_t end_block = block_offset + LicenseBlock::sizeof_block - 1;
	ASSERT_EQ(buffer[end_block], last_byte);
}
#pragma endregion

#pragma region Private
void ProtectKeyTest::printBuffer(const std::string prefix, const value_t& buffer, const offset_t offset, const size_t size) const {
	std::cout << "Start of block offset is: " << offset << std::endl;
	std::cout << "End   of block offset is: " << offset + size - 1 << std::endl;
	for (size_t i = 0; i < size; i++) {
		std::cout << prefix << "buffer[" << offset + i << "] = " << (int)buffer[offset + i] << std::endl;
	}
}
TEST_F(ProtectKeyTest, decode) {
	std::string aes_key_str = "XHQEwGsbezV1ngPFfmLzNhRUy7nTapOj";

	// Generate input with a given length
	const size_t inputslength = 50000;
	byte_t* aes_input = new byte_t[inputslength];
	memset(aes_input, 'X', inputslength);

	// Init vector
	byte_t *iv_enc = new byte_t[AES_BLOCK_SIZE];
	byte_t *iv_dec = new byte_t[AES_BLOCK_SIZE];
	RAND_bytes(iv_enc, AES_BLOCK_SIZE);
	memcpy(iv_dec, iv_enc, AES_BLOCK_SIZE);

	// Buffers for encryption and decryption
	const size_t encslength = ((inputslength + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
	byte_t *enc_out = new byte_t[encslength];
	byte_t *dec_out = new byte_t[inputslength];
	memset(enc_out, 0, encslength);
	memset(dec_out, 0, inputslength);

	// Key to encode
	AES_KEY enc_key;
	AES_set_encrypt_key(reinterpret_cast<const byte_t*>(aes_key_str.data()), AES_key_length, &enc_key);
	AES_cbc_encrypt(aes_input, enc_out, encslength, &enc_key, iv_enc, AES_ENCRYPT);

	// Trying to decode
	byte_t* decoded_buffer = new byte_t[inputslength];
	_protect_key_hasp_sl->decrypt(enc_out, iv_dec, decoded_buffer, inputslength);

	int result = std::memcmp(aes_input, decoded_buffer, inputslength);
	ASSERT_TRUE(result == 0);

	delete[] aes_input;
	delete[] iv_enc;
	delete[] iv_dec;
	delete[] enc_out;
	delete[] dec_out;
	delete[] decoded_buffer;
}
#pragma endregion
