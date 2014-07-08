
#include "stdafx.h"

#include "ProtectKeyHaspSLTest.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"
#include "Platform.h"
#include "ProtectKeyHaspSL.h"
#include "MockRealKeyHaspSL.h"

#pragma region Constructor Destructor
ProtectKeyHaspSLTest::ProtectKeyHaspSLTest() {
}
ProtectKeyHaspSLTest::~ProtectKeyHaspSLTest() {
}
#pragma endregion

#pragma region Public
const protect_key_t ProtectKeyHaspSLTest::create_key(const feature_t feature, const std::wstring session_id, const size_t licenses_amount) {
	const offset_t ro_memory_offset = 3;
	const value_t ro_memory_value = value_t{ 0x10, 0x00, 0x4a, 0x83 };

	check_method_memory_t check_method_memory = std::make_shared<const CheckMethodMemory>(ro_memory_offset, ro_memory_value, nullptr, KeyMemoryType::ReadOnly);
	check_methods_memory_t check_methods_memory{ check_method_memory };

	return create_key(feature, session_id, licenses_amount, check_methods_memory);
}
const protect_key_t ProtectKeyHaspSLTest::create_key(const feature_t feature, const std::wstring session_id, const size_t licenses_amount, const check_methods_memory_t& check_methods_memory) {
	auto real_key = std::make_shared<const MockRealKeyHaspSL>(feature, check_methods_memory);
	real_key->set_licenses_amount(licenses_amount);

	return create_key(real_key, session_id);
}
const protect_key_t ProtectKeyHaspSLTest::create_key(mock_real_key_hasp_sl_t real_key, const std::wstring session_id) {
	auto session_id_hash = ProtectKey::hash_from_session_id(session_id);
	auto protect_key_hasp_sl = std::make_shared<const ProtectKeyHaspSL>(real_key, session_id_hash);

	return protect_key_hasp_sl;
}
#pragma endregion

#pragma region Tests
TEST_F(ProtectKeyHaspSLTest, find_key) {
	protect_keys_t protect_keys = createKeys();
	auto iprotect_key_weak = ProtectKey::find_key(protect_keys, *this);
	ASSERT_TRUE(nullptr != iprotect_key_weak.lock());
}
#pragma endregion

#pragma region Protected
const protect_keys_t ProtectKeyHaspSLTest::createKeys(void) const {
	auto protect_key = ProtectKeyHaspSLTest::create_key(_feature, Platform::platform()->session_id(), _licenses_amount_two);
	protect_key->set_logout_after_check(true);
	const auto checkMethod = protect_key->create_check_method_login(_feature, false);
	checkMethod->set_check_method_for_license(true);
	checkMethod->set_logout_after_check(true);

	protect_keys_t protect_keys;
	protect_keys.push_back(protect_key);

	return protect_keys;
}
void ProtectKeyHaspSLTest::did_check_protect_key(const bool success) {
	ASSERT_TRUE(success);
}
#pragma endregion
