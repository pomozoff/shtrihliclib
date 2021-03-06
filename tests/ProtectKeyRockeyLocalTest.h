
#ifndef __PROTECTKEYROCKELOCALTEST_H__
#define __PROTECTKEYROCKELOCALTEST_H__

#include "gtest/gtest.h"

#include "ProtectKey.h"
#include "IProtectKeyDelegate.h"

class MockRealKeyRockeyLocal;
using mock_real_key_rockey_local_t = std::shared_ptr<const MockRealKeyRockeyLocal>;

class ProtectKeyRockeyLocalTest : public ::testing::Test, public IProtectKeyDelegate {
	public:
		~ProtectKeyRockeyLocalTest(void);

		static const protect_key_t create_key(const feature_t feature);
		static const protect_key_t create_key(const feature_t feature, const check_methods_memory_t& check_methods_memory);
		static const protect_key_t create_key(mock_real_key_rockey_local_t real_key);
	protected:
		ProtectKeyRockeyLocalTest(void);

		const feature_t _feature = 3;
		const size_t _licenses_amount_two = 2;

		const protect_keys_t createKeys(void) const;

		virtual void did_check_protect_key(const bool success) override final;
};

#endif // __PROTECTKEYROCKELOCALTEST_H__
