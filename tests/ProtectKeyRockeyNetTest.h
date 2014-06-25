
#ifndef __PROTECTKEYROCKENETTEST_H__
#define __PROTECTKEYROCKENETTEST_H__

#include "gtest/gtest.h"

#include "ProtectKey.h"
#include "IProtectKeyDelegate.h"

class ProtectKeyRockeyNetTest : public ::testing::Test, public IProtectKeyDelegate {
	public:
		~ProtectKeyRockeyNetTest(void);

		static const protect_key_t create_rockey_net_key(const feature_t feature, const size_t licenses_amount);
		static const protect_key_t create_rockey_net_key(const feature_t feature, const size_t licenses_amount, const check_methods_memory_t& check_methods_memory);
	protected:
		ProtectKeyRockeyNetTest(void);

		const feature_t _feature = 3;
		const size_t _licenses_amount_two = 2;

		const protect_keys_t createKeys(void) const;

		virtual void did_check_protect_key(const bool success) override final;
};

#endif // __PROTECTKEYROCKENETTEST_H__
