
#include "stdafx.h"

#include "LicenseBlockTest.h"
#include "ProtectKeyHaspSL.h"
#include "Platform.h"

#pragma region Constructor Destructor
LicenseBlockTest::LicenseBlockTest(void) {
	_key_memory.resize(ProtectKeyHaspSL::read_write_memory_size);
}
LicenseBlockTest::~LicenseBlockTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(LicenseBlockTest, create_block_as_buffer_from_string) {
	time_t some_time = 1392280873;

	auto session_id = L"(computer-username)";
	auto block = LicenseBlock::block_from_string(session_id, some_time);
	ASSERT_EQ(block.size(), 16);

	ASSERT_EQ(block[0],  232);
	ASSERT_EQ(block[1],  121);
	ASSERT_EQ(block[2],   37);
	ASSERT_EQ(block[3],   55);
	ASSERT_EQ(block[4],   41);
	ASSERT_EQ(block[5],  133);
	ASSERT_EQ(block[6],  252);
	ASSERT_EQ(block[7],   82);
	ASSERT_EQ(block[8],    0);
	ASSERT_EQ(block[9],    0);
	ASSERT_EQ(block[10],   0);
	ASSERT_EQ(block[11],   0);
	ASSERT_EQ(block[12],  34);
	ASSERT_EQ(block[13], 246);
	ASSERT_EQ(block[14], 193);
	ASSERT_EQ(block[15], 217);
}
TEST_F(LicenseBlockTest, is_expired_true) {
	time_t some_time = 1392280873;

	auto session_id = ProtectKey::session_id(Platform::platform());
	auto block = LicenseBlock::block_from_string(session_id, some_time);
	auto offset = LicenseBlock::sizeof_block * 6;
	auto timeout_seconds = 30;
	auto session_id_hash = ProtectKey::hash_from_session_id(session_id);
	auto license_block = std::make_shared<const LicenseBlock>(block, offset, timeout_seconds, session_id_hash);

	auto is_expired = license_block->is_expired();
	ASSERT_TRUE(is_expired);
}
TEST_F(LicenseBlockTest, is_expired_false) {
	time_t some_time;
	time(&some_time);

	auto session_id = ProtectKey::session_id(Platform::platform());
	auto block = LicenseBlock::block_from_string(session_id, some_time);
	auto offset = LicenseBlock::sizeof_block * 4;
	auto timeout_seconds = 30;
	auto session_id_hash = ProtectKey::hash_from_session_id(session_id);
	auto license_block = std::make_shared<const LicenseBlock>(block, offset, timeout_seconds, session_id_hash);

	auto is_expired = license_block->is_expired();
	ASSERT_TRUE(!is_expired);
}
TEST_F(LicenseBlockTest, is_it_my_block_true) {
	time_t some_time = 1392280873;

	auto session_id = ProtectKey::session_id(Platform::platform());

	auto block = LicenseBlock::block_from_string(session_id, some_time);
	auto offset = LicenseBlock::sizeof_block * 7;
	auto timeout_seconds = 30;
	auto session_id_hash = ProtectKey::hash_from_session_id(session_id);
	auto license_block = std::make_shared<const LicenseBlock>(block, offset, timeout_seconds, session_id_hash);

	auto is_it_my_block = license_block->is_it_my_block();
	ASSERT_TRUE(is_it_my_block);
}
TEST_F(LicenseBlockTest, is_it_my_block_false) {
	time_t some_time = 1392280873;

	auto session1_id = L"(computer-alex)";
	auto session2_id = L"(computer-test)";

	auto block = LicenseBlock::block_from_string(session1_id, some_time);
	auto offset = LicenseBlock::sizeof_block * 7;
	auto timeout_seconds = 30;
	auto session_id_hash = ProtectKey::hash_from_session_id(session2_id);
	auto license_block = std::make_shared<const LicenseBlock>(block, offset, timeout_seconds, session_id_hash);

	auto is_it_my_block = license_block->is_it_my_block();
	ASSERT_TRUE(!is_it_my_block);
}
#pragma endregion
