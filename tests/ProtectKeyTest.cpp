
#include "stdafx.h"

#include "ProtectKeyTest.h"
#include "Platform.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"
#include "ProtectKeyHaspSLTest.h"
#include "MockRealKeyHaspSL.h"

#pragma region Constructor Destructor
ProtectKeyTest::ProtectKeyTest(void) {
}
ProtectKeyTest::~ProtectKeyTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(ProtectKeyTest, hasp_sl_key) {
	protect_keys_t protect_keys;
	protect_keys.push_back(create_key_hasp_sl());

	auto iprotect_key_weak = ProtectKey::find_key(protect_keys, *this);
	auto iprotect_key = iprotect_key_weak.lock();
	ASSERT_TRUE(nullptr != iprotect_key);

	_check_license_expected_result = true;
	auto is_license_present = iprotect_key->check_license();
	ASSERT_TRUE(is_license_present);
}
#pragma endregion

#pragma region Protecetd
const protect_key_t ProtectKeyTest::create_key_hasp_sl(void) const {
	auto key = std::make_shared<const MockRealKeyHaspSL>(_feature_hasp_sl, check_methods_memory_t());
	key->set_licenses_amount(_licenses_amount_two);

	auto protect_key = ProtectKeyHaspSLTest::create_key(_feature_hasp_sl, Platform::platform()->session_id(), _licenses_amount_two);
	const auto checkMethod = protect_key->create_check_method_login(_feature_hasp_sl, false);
	checkMethod->set_check_method_for_license(true);
	checkMethod->set_logout_after_check(true);


	return protect_keys;
}
void ProtectKeyTest::did_check_protect_key(const bool success) {
	ASSERT_TRUE(success == _check_license_expected_result);
}
#pragma endregion
