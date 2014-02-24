
#pragma once

#include <functional>

#include "DataTypes.h"

class LicenseBlockManager final {
	public:
		LicenseBlockManager(const value_t buffer, const time_t timeout, const size_t licenses_amount);
		~LicenseBlockManager(void);

		const license_block_t take_license(void) const;
	protected:
		const license_block_t find_my_block(void) const;
	private:
		license_blocks_t _license_blocks;
		const size_t _licenses_amount;

		using p_block_func_t = const bool(LicenseBlock::*)() const;

		const license_blocks_t license_blocks_from_buffer(const value_t& buffer, const time_t timeout) const;
		const license_block_t find_block(p_block_func_t function_checker) const;
		const license_block_t find_first_free_block(void) const;
};
