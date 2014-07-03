
#ifndef __PROTECTKEYTEST_H__
#define __PROTECTKEYTEST_H__

#include "gtest/gtest.h"

#include "ProtectKey.h"
#include "IProtectKeyDelegate.h"

class ProtectKeyTest : public ::testing::Test, public IProtectKeyDelegate {
	public:
		ProtectKeyTest(void);
		~ProtectKeyTest(void);
	protected:
		bool _check_license_expected_result = false;

		const protect_key_t create_key_hasp_sl(void) const;
	private:
		const feature_t _feature_hasp_sl = 3;
		const std::wstring _session_id = L"(computer-username)";
		const size_t _licenses_amount_two = 2;

		virtual void did_check_protect_key(const bool success) override final;
};

#endif // __PROTECTKEYTEST_H__
