
#include "stdafx.h"

#include <openssl/aes.h>
#include <openssl/rand.h>

#include "DecryptTest.h"
#include "ProtectKeyHaspSL.h"
#include "Platform.h"

#pragma region Constructor Destructor
DecryptTest::DecryptTest(void)
	: _protect_key_hasp_sl(ProtectKey::create_key(KeyType::HaspSL, Platform::platform()))
{
}
DecryptTest::~DecryptTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(DecryptTest, decrypt) {
	// Generate input with a given length
	const size_t input_length = 50000;
	byte_t* aes_input = new byte_t[input_length];
	std::memset(aes_input, 'X', input_length);

	byte_t* iv_enc = NULL;
	size_t iv_length = 0;

	byte_t* enc_out = NULL;
	size_t encrypted_length = 0;
	_protect_key_hasp_sl->encrypt(aes_input, input_length, &iv_enc, iv_length, &enc_out, encrypted_length);

	byte_t* dec_out = NULL;
	_protect_key_hasp_sl->decrypt(enc_out, encrypted_length, iv_enc, &dec_out);

	int result = std::memcmp(aes_input, dec_out, input_length);
	ASSERT_TRUE((dec_out) && (result == 0));

	delete[] aes_input;
	delete[] iv_enc;
	delete[] enc_out;
	delete[] dec_out;
}
#pragma endregion
