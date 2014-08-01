
#include "stdafx.h"

#include "CheckMethodLoginTest.h"
#include "CheckMethodLogin.h"
#include "ProtectKeyHaspSLTest.h"
#include "LicenseBlock.h"
#include "ProtectKeyHaspSL.h"

#pragma region Constructor Destructor
CheckMethodLoginTest::CheckMethodLoginTest(void) {
	_check_method = _protect_key_hasp_sl->create_check_method_login(_feature, false);
}
CheckMethodLoginTest::~CheckMethodLoginTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(CheckMethodLoginTest, check_method_type) {
	auto check_method_type = _check_method->check_method_type();
	ASSERT_TRUE(check_method_type == CheckMethodType::Login);
}
TEST_F(CheckMethodLoginTest, check) {
	auto successful_checked = _check_method->check(_protect_key_hasp_sl);
	ASSERT_TRUE(successful_checked);
}
TEST_F(CheckMethodLoginTest, check_licenses_counter_amount_is_null) {
	auto protect_key_hasp_sl1 = ProtectKeyHaspSLTest::create_key(_feature, L"(computer-username1)", _licenses_amount_null);
	auto successful_checked = _check_method->check(protect_key_hasp_sl1);
	ASSERT_TRUE(!successful_checked);
}
TEST_F(CheckMethodLoginTest, check_licenses_counter) {
	//-------------------------------------------------------------------------------------------------------------------
	auto session_id1 = L"(computer-username1)";
	auto session_id2 = L"(computer-username2)";
	auto session_id3 = L"(computer-username3)";

	auto block1 = LicenseBlock::block_from_string(session_id1, time(NULL));
	const offset_t offset1 = 0 * block1.size();
	auto check_method_memory1 = std::make_shared<const CheckMethodMemory>(offset1, block1, nullptr, KeyMemoryType::ReadWrite);

	auto block2 = LicenseBlock::block_from_string(session_id2, time(NULL));
	const offset_t offset2 = 1 * block2.size();
	auto check_method_memory2 = std::make_shared<const CheckMethodMemory>(offset2, block2, nullptr, KeyMemoryType::ReadWrite);

	const check_methods_memory_t check_methods_memory = { check_method_memory1, check_method_memory2 };
	auto real_key = std::make_shared<const MockRealKeyHaspSL>(_feature, check_methods_memory);
	//-------------------------------------------------------------------------------------------------------------------
	real_key->set_licenses_amount(_licenses_amount_one);
	//-------------------------------------------------------------------------------------------------------------------
	auto my_protect_key_hasp_sl1 = ProtectKeyHaspSLTest::create_key(real_key, session_id1);
	auto successful_checked1 = _check_method->check(my_protect_key_hasp_sl1);
	ASSERT_TRUE(successful_checked1);

	auto my_protect_key_hasp_sl2 = ProtectKeyHaspSLTest::create_key(real_key, session_id2);
	auto successful_checked2 = _check_method->check(my_protect_key_hasp_sl2);
	ASSERT_TRUE(!successful_checked2);
	//-------------------------------------------------------------------------------------------------------------------
	my_protect_key_hasp_sl1->logout(true);
	real_key->set_licenses_amount(_licenses_amount_two);
	real_key->set_max_logins_amount(_licenses_amount_two);
	//-------------------------------------------------------------------------------------------------------------------
	auto my_protect_key_hasp_sl3 = ProtectKeyHaspSLTest::create_key(real_key, session_id2);
	auto successful_checked3 = _check_method->check(my_protect_key_hasp_sl3);
	my_protect_key_hasp_sl3->logout(true);
	ASSERT_TRUE(successful_checked3);

	auto my_protect_key_hasp_sl4 = ProtectKeyHaspSLTest::create_key(real_key, session_id3);
	auto successful_checked4 = _check_method->check(my_protect_key_hasp_sl4);
	ASSERT_TRUE(!successful_checked4);
}
#pragma endregion
