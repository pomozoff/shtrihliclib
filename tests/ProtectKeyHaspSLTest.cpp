
#include "stdafx.h"

#include "ProtectKeyHaspSLTest.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"
#include "Platform.h"

#pragma region Constructor Destructor
ProtectKeyHaspSLTest::ProtectKeyHaspSLTest() {
}
ProtectKeyHaspSLTest::~ProtectKeyHaspSLTest() {
}
#pragma endregion

#pragma region Public
const protect_key_t ProtectKeyHaspSLTest::create_hasp_sl_key(const feature_t feature, const std::string session_id, const size_t licenses_amount) {
	const offset_t ro_memory_offset = 3;
	const value_t ro_memory_value = value_t{ 0x10, 0x00, 0x4a, 0x83 };

	check_method_memory_t check_method_memory = std::make_shared<const CheckMethodMemory>(ro_memory_offset, ro_memory_value, nullptr, KeyMemoryType::ReadOnly);
	check_methods_memory_t check_methods_memory{ check_method_memory };

	return create_hasp_sl_key(feature, session_id, licenses_amount, check_methods_memory);
}
const protect_key_t ProtectKeyHaspSLTest::create_hasp_sl_key(const feature_t feature, const std::string session_id, const size_t licenses_amount, const check_methods_memory_t& check_methods_memory) {
	auto session_id_hash = ProtectKey::hash_from_session_id(session_id);
	auto key = std::make_shared<const MockRealKeyHaspSL>(feature, check_methods_memory);
	key->set_licenses_amount(licenses_amount);

	auto protect_key_hasp_sl = std::make_shared<const ProtectKeyHaspSL>(key, session_id_hash);
	protect_key_hasp_sl->set_logout_after_check(true);

	return protect_key_hasp_sl;
}
#pragma endregion

#pragma region Protecetd
const protect_keys_t ProtectKeyHaspSLTest::createKeys(void) const {
	auto protectKey = ProtectKeyHaspSLTest::create_hasp_sl_key(_feature, Platform::platform()->session_id(), _licenses_amount_two);
	const auto checkMethod = protectKey->create_check_method_login(_feature, false);
	checkMethod->set_check_method_for_license(true);
	checkMethod->set_logout_after_check(true);

	protect_keys_t protect_keys;
	protect_keys.push_back(protectKey);

	return protect_keys;
}
#pragma endregion
