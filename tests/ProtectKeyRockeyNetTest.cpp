
#include "stdafx.h"

#include "ProtectKeyRockeyNetTest.h"
#include "ProtectKeyRockeyNet.h"
#include "MockRealKeyRockeyNet.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"

#pragma region Constructor Destructor
ProtectKeyRockeyNetTest::ProtectKeyRockeyNetTest() {
}
ProtectKeyRockeyNetTest::~ProtectKeyRockeyNetTest() {
}
#pragma endregion

#pragma region Public
const protect_key_t ProtectKeyRockeyNetTest::create_key(const feature_t feature, const size_t licenses_amount) {
	const offset_t ro_memory_offset = 3;
	const value_t ro_memory_value = value_t{ 0x10, 0x00, 0x4a, 0x83 };

	check_method_memory_t check_method_memory = std::make_shared<const CheckMethodMemory>(ro_memory_offset, ro_memory_value, nullptr, KeyMemoryType::ReadOnly);
	check_methods_memory_t check_methods_memory{ check_method_memory };

	return create_key(feature, licenses_amount, check_methods_memory);
}
const protect_key_t ProtectKeyRockeyNetTest::create_key(const feature_t feature, const size_t licenses_amount, const check_methods_memory_t& check_methods_memory) {
	auto real_key = std::make_shared<const MockRealKeyRockeyNet>(feature, check_methods_memory);
	real_key->initialize_memory(check_methods_memory);

	return create_key(real_key);
}
const protect_key_t ProtectKeyRockeyNetTest::create_key(mock_real_key_rockey_net_t real_key) {
	auto protect_key_rockey_net = std::make_shared<const ProtectKeyRockeyNet>(real_key);
	protect_key_rockey_net->set_logout_after_check(true);

	return protect_key_rockey_net;
}
#pragma endregion

#pragma region Tests
TEST_F(ProtectKeyRockeyNetTest, find_key) {
	protect_keys_t protect_keys = createKeys();
	auto iprotect_key_weak = ProtectKey::find_key(protect_keys, *this);
	ASSERT_TRUE(nullptr != iprotect_key_weak.lock());
}
#pragma endregion

#pragma region Protected
const protect_keys_t ProtectKeyRockeyNetTest::createKeys(void) const {
	auto protectKey = ProtectKeyRockeyNetTest::create_key(_feature, _licenses_amount_two);
	const auto checkMethod = protectKey->create_check_method_login(_feature, false);
	checkMethod->set_check_method_for_license(true);
	checkMethod->set_logout_after_check(true);

	protect_keys_t protect_keys;
	protect_keys.push_back(protectKey);

	return protect_keys;
}
void ProtectKeyRockeyNetTest::did_check_protect_key(const bool success) {
	ASSERT_TRUE(success);
}
#pragma endregion
