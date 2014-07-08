
#include "stdafx.h"

#include "ProtectKeyTest.h"
#include "Platform.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"
#include "Granule.h"

#include "ProtectKeyHaspSLTest.h"
#include "MockRealKeyHaspSL.h"

#include "ProtectKeyRockeyLocalTest.h"
#include "MockRealKeyRockeyLocal.h"

#include "ProtectKeyRockeyNetTest.h"
#include "MockRealKeyRockeyNet.h"

#pragma region Constructor Destructor
ProtectKeyTest::ProtectKeyTest(void)
	: _mock_real_key_hasp_sl(std::make_shared<const MockRealKeyHaspSL>(_feature_hasp_sl, check_methods_memory_t()))
	, _mock_real_key_rockey_local(std::make_shared<const MockRealKeyRockeyLocal>(_feature_rockey_local, check_methods_memory_t()))
	, _mock_real_key_rockey_net_nfr(std::make_shared<const MockRealKeyRockeyNet>(_feature_rockey_net_nfr, check_methods_memory_t(), true))
	, _mock_real_key_rockey_net(std::make_shared<const MockRealKeyRockeyNet>(_feature_rockey_net, check_methods_memory_t(), false))
	, _protect_key_hasp_sl(create_key_hasp_sl(_mock_real_key_hasp_sl))
	, _protect_key_rockey_local(create_key_rockey_local(_mock_real_key_rockey_local))
	, _protect_key_rockey_net_nfr(create_key_rockey_net(_mock_real_key_rockey_net_nfr))
	, _protect_key_rockey_net(create_key_rockey_net(_mock_real_key_rockey_net))
{
	_mock_real_key_hasp_sl->set_licenses_amount(_licenses_amount_two);
	_mock_real_key_hasp_sl->set_max_logins_amount(_logins_amount_one);

	_mock_real_key_rockey_net->set_licenses_amount(_licenses_amount_two);
	
	_mock_real_key_rockey_net_nfr->set_licenses_amount(_licenses_amount_ten);
	_mock_real_key_rockey_net_nfr->set_is_key_nfr(true);
}
ProtectKeyTest::~ProtectKeyTest(void) {
}
#pragma endregion

#pragma region Tests
TEST_F(ProtectKeyTest, find_every_key) {
	protect_keys_t protect_keys{ _protect_key_hasp_sl, _protect_key_rockey_local, _protect_key_rockey_net_nfr, _protect_key_rockey_net };
	iprotect_key_t iprotect_key = nullptr;

	// Ищем ключ HASP SL
	iprotect_key = find_next_key(protect_keys);
	ASSERT_TRUE(nullptr != iprotect_key);
	ASSERT_EQ(0, _mock_real_key_hasp_sl->logged_in_users_amount());
	check_key_license(iprotect_key, _mock_real_key_hasp_sl);

	// Ищем следующий ключ Rockey Local
	iprotect_key = find_next_key(protect_keys);
	ASSERT_TRUE(nullptr != iprotect_key);
	ASSERT_EQ(0, _mock_real_key_rockey_local->logged_in_users_amount());
	check_key_license(iprotect_key, _mock_real_key_rockey_local);

	// Ищем следующий ключ Rockey Net NFR
	iprotect_key = find_next_key(protect_keys);
	ASSERT_TRUE(nullptr != iprotect_key);
	ASSERT_EQ(0, _mock_real_key_rockey_net_nfr->logged_in_users_amount());
	check_key_license(iprotect_key, _mock_real_key_rockey_net_nfr);

	// Ищем следующий ключ Rockey Net
	iprotect_key = find_next_key(protect_keys);
	ASSERT_TRUE(nullptr != iprotect_key);
	ASSERT_EQ(1, _mock_real_key_rockey_net->logged_in_users_amount());
	check_key_license(iprotect_key, _mock_real_key_rockey_net);
}
TEST_F(ProtectKeyTest, rockey_net_check_correct_logins_amount) {
	auto protect_key_rockey_net1 = create_key_rockey_net(_mock_real_key_rockey_net);
	protect_keys_t protect_keys1{ protect_key_rockey_net1 };
	iprotect_key_t iprotect_key1 = find_next_key(protect_keys1);
	ASSERT_TRUE(nullptr != iprotect_key1);
	ASSERT_EQ(1, _mock_real_key_rockey_net->logged_in_users_amount());

	auto protect_key_rockey_net2 = create_key_rockey_net(_mock_real_key_rockey_net);
	protect_keys_t protect_keys2{ protect_key_rockey_net2 };
	iprotect_key_t iprotect_key2 = find_next_key(protect_keys2);
	ASSERT_TRUE(nullptr != iprotect_key2);
	ASSERT_EQ(2, _mock_real_key_rockey_net->logged_in_users_amount());

	auto protect_key_rockey_net3 = create_key_rockey_net(_mock_real_key_rockey_net);
	protect_keys_t protect_keys3{ protect_key_rockey_net3 };
	iprotect_key_t iprotect_key3 = find_next_key(protect_keys3);
	ASSERT_TRUE(nullptr == iprotect_key3);
	ASSERT_EQ(2, _mock_real_key_rockey_net->logged_in_users_amount());
}
TEST_F(ProtectKeyTest, rockey_net_nfr_check_correct_logins_amount) {
	for (size_t i = 1; i < _licenses_amount_ten * 2; ++i) {
		auto protect_key_rockey_net_nfr = create_key_rockey_net(_mock_real_key_rockey_net_nfr);
		protect_keys_t protect_keys{ protect_key_rockey_net_nfr };
		iprotect_key_t iprotect_key = find_next_key(protect_keys);
		ASSERT_TRUE(nullptr != iprotect_key);
		ASSERT_EQ(0, _mock_real_key_rockey_net_nfr->logged_in_users_amount());
	}
}
#pragma endregion

#pragma region Protected
const protect_key_t ProtectKeyTest::create_key_hasp_sl(const mock_real_key_hasp_sl_t mock_real_key) const {
	auto protect_key = ProtectKeyHaspSLTest::create_key(mock_real_key, Platform::platform()->session_id());
	
	const auto check_method = protect_key->create_check_method_login(_feature_hasp_sl, false);
	check_method->set_check_method_for_license(true);
	protect_key->set_logout_after_check(true);

	return protect_key;
}
const protect_key_t ProtectKeyTest::create_key_rockey_local(const mock_real_key_rockey_local_t mock_real_key) const {
	auto protect_key = ProtectKeyRockeyLocalTest::create_key(mock_real_key);

	const auto check_method = protect_key->create_check_method_login(_feature_rockey_local, false);
	check_method->set_check_method_for_license(true);
	protect_key->set_logout_after_check(true);

	add_granules_for_key_rockey(protect_key, check_method);

	return protect_key;
}
const protect_key_t ProtectKeyTest::create_key_rockey_net(const mock_real_key_rockey_net_t mock_real_key) const {
	auto protect_key = ProtectKeyRockeyNetTest::create_key(mock_real_key);

	const offset_t offset_nfr_key = 8;
	const value_t value_nfr = value_t{ 0x00, 0x00 };

	const value_t value_key = value_t{ 0xdf, 0x3d };

	const auto check_method_nfr = protect_key->create_check_method_login(_feature_rockey_net_nfr, false);
	check_method_nfr->set_check_method_for_nfr(true);
	check_method_nfr->set_logout_after_check(true);

	auto nfr_granule = protect_key->create_granule(_granule_name_nfr);
	nfr_granule->create_check_method_memory(offset_nfr_key, value_nfr, check_method_nfr);
	nfr_granule->set_granule_nfr_date(true);
	nfr_granule->set_read_memory_to_value(true);

	const auto check_method = protect_key->create_check_method_login(_feature_rockey_net, false);
	check_method->set_check_method_for_license(true);

	add_granules_for_key_rockey(protect_key, check_method);

	return protect_key;
}
void ProtectKeyTest::add_granules_for_key_rockey(const protect_key_t protect_key, const check_method_login_t check_method) const {
	const offset_t offset_caches_amount = 3;
	const value_t value_caches_amount = value_t{ 0x00 };

	auto granule = protect_key->create_granule(_granule_name_cache_amount);
	granule->create_check_method_memory(offset_caches_amount, value_caches_amount, check_method);
	granule->set_read_memory_to_value(true);
}
#pragma endregion

#pragma region Protect Key Delegate
void ProtectKeyTest::did_check_protect_key(const bool success) {
	ASSERT_TRUE(success == _check_license_expected_result);
}
#pragma endregion

#pragma region Protected
const iprotect_key_t ProtectKeyTest::find_next_key(const protect_keys_t protect_keys) {
	auto iprotect_key_weak = ProtectKey::find_key(protect_keys, *this);
	return iprotect_key_weak.lock();
}
void ProtectKeyTest::check_key_license(const iprotect_key_t iprotect_key, const mock_real_key_t mock_real_key) {
	bool is_license_present = false;
	_check_license_expected_result = true;

	// Проверяем наличие лицензии
	is_license_present = iprotect_key->check_license();
	ASSERT_TRUE(is_license_present);

	// Отключаем ключ
	mock_real_key->set_enabled(false);
	// Сообщаем делегату, что ключа нет
	_check_license_expected_result = false;

	// Пытаемся проверить лицензию на отсутствующем ключе
	auto max_check_number = iprotect_key->max_check_number();
	for (size_t i = 1; i < max_check_number; ++i) {
		is_license_present = iprotect_key->check_license();
		ASSERT_TRUE(is_license_present);
	}

	// Последняя попытка проверки лицензии на отсутствующем ключе
	is_license_present = iprotect_key->check_license();
	ASSERT_FALSE(is_license_present);
}
#pragma endregion
