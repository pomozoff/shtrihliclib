
#ifndef __PROTECTKEYTEST_H__
#define __PROTECTKEYTEST_H__

#include "gtest/gtest.h"

#include "ProtectKey.h"
#include "IProtectKeyDelegate.h"

class MockRealKey;
class MockRealKeyHaspSL;
class MockRealKeyRockeyLocal;
class MockRealKeyRockeyNet;

using mock_real_key_t = std::shared_ptr<const MockRealKey>;
using mock_real_key_hasp_sl_t = std::shared_ptr<const MockRealKeyHaspSL>;
using mock_real_key_rockey_local_t = std::shared_ptr<const MockRealKeyRockeyLocal>;
using mock_real_key_rockey_net_t = std::shared_ptr<const MockRealKeyRockeyNet>;

class ProtectKeyTest : public ::testing::Test, public IProtectKeyDelegate {
	public:
		ProtectKeyTest(void);
		~ProtectKeyTest(void);
	private:
		const std::wstring _granule_name_cache_amount = L"Количество касс";
		const std::wstring _granule_name_nfr = L"НФР";
	protected:
		bool _check_license_expected_result = false;

		const feature_t _feature_hasp_sl = 3;
		const feature_t _feature_rockey_local = 1;
		const feature_t _feature_rockey_net = 11;

		const std::wstring _session_id = L"(computer-username)";
		const size_t _licenses_amount_two = 2;

		const mock_real_key_hasp_sl_t      _mock_real_key_hasp_sl;
		const mock_real_key_rockey_local_t _mock_real_key_rockey_local;
		const mock_real_key_rockey_net_t   _mock_real_key_rockey_net;

		const protect_key_t _protect_key_hasp_sl;
		const protect_key_t _protect_key_rockey_local;
		const protect_key_t _protect_key_rockey_net;

		const protect_key_t create_key_hasp_sl(const mock_real_key_hasp_sl_t mock_real_key) const;
		const protect_key_t create_key_rockey_local(const mock_real_key_rockey_local_t mock_real_key) const;
		const protect_key_t create_key_rockey_net(const mock_real_key_rockey_net_t mock_real_key) const;

		void add_granules_for_key_rockey(const protect_key_t protect_key, const check_method_login_t check_method) const;
		void find_next_key(const protect_keys_t protect_keys, const mock_real_key_t mock_real_key);
	private:
		virtual void did_check_protect_key(const bool success) override final;
};

#endif // __PROTECTKEYTEST_H__
