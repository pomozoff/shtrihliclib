
#include "stdafx.h"

#include "LicenseBlockTest.h"
#include "ProtectKeyHaspSL.h"

LicenseBlockTest::LicenseBlockTest() {
	_key_memory.resize(ProtectKeyHaspSL::ReadWriteMemorySize);
}
LicenseBlockTest::~LicenseBlockTest() {
}

TEST_F(LicenseBlockTest, create_block_as_buffer_from_string) {
	time_t some_time = 1392280873;
	auto block = LicenseBlock::create_block_as_buffer_from_string(R"(computer-username)", some_time);
	ASSERT_EQ(block.size(), 16);

	ASSERT_EQ(block[0],  119);
	ASSERT_EQ(block[1],  212);
	ASSERT_EQ(block[2],   48);
	ASSERT_EQ(block[3],   74);
	ASSERT_EQ(block[4],   41);
	ASSERT_EQ(block[5],  133);
	ASSERT_EQ(block[6],  252);
	ASSERT_EQ(block[7],   82);
	ASSERT_EQ(block[8],    0);
	ASSERT_EQ(block[9],    0);
	ASSERT_EQ(block[10],   0);
	ASSERT_EQ(block[11],   0);
	ASSERT_EQ(block[12], 168);
	ASSERT_EQ(block[13], 116);
	ASSERT_EQ(block[14], 191);
	ASSERT_EQ(block[15],  89);
}
}
