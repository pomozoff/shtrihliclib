
#ifndef __LICENSEBLOCKMANAGER_H__
#define __LICENSEBLOCKMANAGER_H__

#include <functional>

class LicenseBlockManager final {
	public:
		LicenseBlockManager(const value_t buffer, const time_t timeout, const size_t licenses_amount, const size_t session_id_hash);
		~LicenseBlockManager(void);

		const license_block_t take_license(void) const;
		const license_block_t find_my_block(void) const;
	protected:
	private:
		LicenseBlockManager& operator=(const LicenseBlockManager &tmp);

		license_blocks_t _license_blocks;
		const size_t _licenses_amount;

		using p_block_func_t = const bool(LicenseBlock::*)(void) const;

		const license_blocks_t license_blocks_from_buffer(const value_t& buffer, const time_t timeout, const size_t session_id_hash) const;
		const license_block_t find_block(p_block_func_t function_checker) const;
		const license_block_t find_first_free_block(void) const;
};

#endif // __LICENSEBLOCKMANAGER_H__
