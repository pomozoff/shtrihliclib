
#include "stdafx.h"

#include "LicenseBlockManagerTest.h"
#include "LicenseBlock.h"
#include "ProtectKeyHaspSL.h"

#pragma region Constructor Destructor
LicenseBlockManagerTest::LicenseBlockManagerTest() {
}
LicenseBlockManagerTest::~LicenseBlockManagerTest() {
}
#pragma endregion Constructor Destructor

#pragma region Tests
TEST_F(LicenseBlockManagerTest, take_license) {
	const value_t buffer(ProtectKeyHaspSL::read_write_memory_size, 0);
	const time_t timeout = 30;
	const size_t licenses_amount = 2;

	value_t buffer(sizeof_buffer);
	std::fill(buffer.begin(), buffer.end(), 0);

	auto manager = std::make_shared<const LicenseBlockManager>(buffer, timeout, licenses_amount);
	auto license_block = manager->take_license();

	ASSERT_TRUE(nullptr != license_block);
	ASSERT_TRUE(!license_block->is_expired());
	ASSERT_TRUE(license_block->is_it_my_block());
}
#pragma endregion Tests
