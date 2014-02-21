
#pragma once

#include "DataTypes.h"

class LicenseBlockManager final {
	public:
		LicenseBlockManager(const value_t buffer, const time_t timeout, const size_t licenses_amount);
		~LicenseBlockManager(void);
	private:
		const license_blocks_t _license_blocks;
		const time_t _timeout;
		const size_t _licenses_amount;
};
