
#include "stdafx.h"

#include "GranuleTest.h"
#include "ProtectKeyHaspSL.h"
#include "Granule.h"
#include "Platform.h"
#include "CheckMethodLogin.h"
#include "MockRealKeyHaspSL.h"

#pragma region Constructor Destructor
GranuleTest::GranuleTest(void)
	: _iprotect_key(create_protect_key())
{
}
GranuleTest::~GranuleTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(GranuleTest, no_granule_with_wrong_name) {
	auto granule = _iprotect_key->granule_with_name(L"");
	ASSERT_TRUE(granule == nullptr);
}
TEST_F(GranuleTest, has_granule_with_correct_name) {
	auto granule = _iprotect_key->granule_with_name(_granule_name);
	ASSERT_TRUE(granule != nullptr);
	ASSERT_TRUE(granule->name() == _granule_name);
}
#pragma endregion

#pragma region Private
const protect_key_t GranuleTest::create_protect_key(void) const {
	const feature_t feature = 4;
	const check_methods_memory_t check_methods_memory;
	auto session_id = L"(computer-username1)";
	auto session_id_hash = ProtectKey::hash_from_session_id(session_id);

	auto real_key = std::make_shared<const MockRealKeyHaspSL>(feature, check_methods_memory);
	auto protect_key = std::make_shared<const ProtectKeyHaspSL>(real_key, session_id_hash);

	const auto checkMethod = protect_key->create_check_method_login(feature, false);
	checkMethod->set_check_method_for_license(true);
	checkMethod->set_logout_after_check(true);

	const offset_t offset_caches_amount = 23;
	const value_t value_caches_amount = value_t{ 0x00 };

	auto granule = protect_key->create_granule(_granule_name);
	granule->create_check_method_memory(offset_caches_amount, value_caches_amount, checkMethod);
	granule->set_read_memory_to_value(true);

	return protect_key;
}
#pragma endregion
