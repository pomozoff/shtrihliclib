
#include "stdafx.h"

#include "LicenseBlockManagerTest.h"

LicenseBlockManagerTest::LicenseBlockManagerTest() {
}
LicenseBlockManagerTest::~LicenseBlockManagerTest() {
}

TEST_F(LicenseBlockManagerTest, take_license) {
	const size_t sizeof_buffer = 4096;
	const time_t timeout = 30;
	const size_t licenses_amount = 2;

	value_t buffer(sizeof_buffer);
	std::fill(buffer.begin(), buffer.end(), 0);

	auto manager = std::make_shared<const LicenseBlockManager>(buffer, timeout, licenses_amount);
	auto license_block = manager->take_license();

	ASSERT_TRUE(nullptr != license_block);
}
