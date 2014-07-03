
#include "stdafx.h"

#include "ProtectKeyTest.h"
#include "ProtectKeyHaspSLTest.h"
#include "Platform.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"

#pragma region Constructor Destructor
ProtectKeyTest::ProtectKeyTest(void) {
}
ProtectKeyTest::~ProtectKeyTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(ProtectKeyTest, hasp_sl_key) {
	auto protect_keys = createKeysOneHaspSL();
	auto iprotect_key_weak = ProtectKey::find_key(protect_keys, *this);
	ASSERT_TRUE(nullptr != iprotect_key_weak.lock());
}
#pragma endregion

#pragma region Protecetd
const protect_keys_t ProtectKeyTest::createKeysOneHaspSL(void) const {
	auto protectKey = ProtectKeyHaspSLTest::create_hasp_sl_key(_feature_hasp_sl, Platform::platform()->session_id(), _licenses_amount_two);
	const auto checkMethod = protectKey->create_check_method_login(_feature_hasp_sl, false);
	checkMethod->set_check_method_for_license(true);
	checkMethod->set_logout_after_check(true);

	protect_keys_t protect_keys;
	protect_keys.push_back(protectKey);

	return protect_keys;
}
void ProtectKeyTest::did_check_protect_key(const bool success) {
	ASSERT_TRUE(success);
}
#pragma endregion
