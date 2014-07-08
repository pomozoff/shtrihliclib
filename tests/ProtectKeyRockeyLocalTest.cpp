
#include "stdafx.h"

#include "ProtectKeyRockeyLocalTest.h"
#include "ProtectKeyRockeyLocal.h"
#include "MockRealKeyRockeyLocal.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"

#pragma region Constructor Destructor
ProtectKeyRockeyLocalTest::ProtectKeyRockeyLocalTest() {
}
ProtectKeyRockeyLocalTest::~ProtectKeyRockeyLocalTest() {
}
#pragma endregion

#pragma region Public
const protect_key_t ProtectKeyRockeyLocalTest::create_key(const feature_t feature) {
	const offset_t ro_memory_offset = 3;
	const value_t ro_memory_value = value_t{ 0x10, 0x00, 0x4a, 0x83 };

	check_method_memory_t check_method_memory = std::make_shared<const CheckMethodMemory>(ro_memory_offset, ro_memory_value, nullptr, KeyMemoryType::ReadOnly);
	check_methods_memory_t check_methods_memory{ check_method_memory };

	return create_key(feature, check_methods_memory);
}
const protect_key_t ProtectKeyRockeyLocalTest::create_key(const feature_t feature, const check_methods_memory_t& check_methods_memory) {
	auto real_key = std::make_shared<const MockRealKeyRockeyLocal>(feature, check_methods_memory);
	real_key->initialize_memory(check_methods_memory);

	return create_key(real_key);
}
const protect_key_t ProtectKeyRockeyLocalTest::create_key(mock_real_key_rockey_local_t real_key) {
	auto protect_key_rockey_local = std::make_shared<const ProtectKeyRockeyLocal>(real_key);

	return protect_key_rockey_local;
}
#pragma endregion

#pragma region Tests
TEST_F(ProtectKeyRockeyLocalTest, find_key) {
	protect_keys_t protect_keys = createKeys();
	auto iprotect_key_weak = ProtectKey::find_key(protect_keys, *this);
	ASSERT_TRUE(nullptr != iprotect_key_weak.lock());
}
#pragma endregion

#pragma region Protected
const protect_keys_t ProtectKeyRockeyLocalTest::createKeys(void) const {
	auto protect_key = ProtectKeyRockeyLocalTest::create_key(_feature);
	protect_key->set_logout_after_check(true);
	const auto checkMethod = protect_key->create_check_method_login(_feature, false);
	checkMethod->set_check_method_for_license(true);
	checkMethod->set_logout_after_check(true);

	protect_keys_t protect_keys;
	protect_keys.push_back(protect_key);

	return protect_keys;
}
void ProtectKeyRockeyLocalTest::did_check_protect_key(const bool success) {
	ASSERT_TRUE(success);
}
#pragma endregion
