
#include "stdafx.h"

#include "LicenseBlockTest.h"

LicenseBlockTest::LicenseBlockTest() {
}
LicenseBlockTest::~LicenseBlockTest() {
}

TEST_F(LicenseBlockTest, check) {
	auto license_block = LicenseBlock::create_block_as_buffer_from_string(R"()", time(NULL));
	bool successful_checked = false;
	ASSERT_TRUE(successful_checked);
}
