
#include "stdafx.h"

#include <algorithm>
#include <memory>
#include <ctime>

#include "LicenseBlockManager.h"
#include "LicenseBlock.h"

#pragma region Constructor Destructor
LicenseBlockManager::LicenseBlockManager(const value_t buffer, const time_t timeout, const size_t licenses_amount) :
_licenses_amount(licenses_amount),
_license_blocks(license_blocks_from_buffer(buffer, timeout))
{
}
LicenseBlockManager::~LicenseBlockManager(void) {
}
#pragma endregion Constructor Destructor

#pragma region Public
const license_block_t LicenseBlockManager::take_license(void) const {
	license_block_t block = find_my_block();
	if (!block) {
		block = find_first_free_block();
	}
	if (block) {
		block->update_block(time(NULL));
	}
	return block;
}
const license_block_t LicenseBlockManager::find_my_block(void) const {
	return find_block(&LicenseBlock::is_it_my_block);
}
#pragma endregion Public

#pragma region Private
const license_blocks_t LicenseBlockManager::license_blocks_from_buffer(const value_t& buffer, const time_t timeout) const {
	int32_t block_size = LicenseBlock::sizeof_block;
	license_blocks_t license_blocks;
	license_blocks.reserve(buffer.size() / block_size);

	auto buffer_iterator_begin_block = buffer.begin();
	while ((buffer.end() - buffer_iterator_begin_block) >= block_size) {
		auto buffer_iterator_end_block = buffer_iterator_begin_block + block_size;
		value_t block(block_size);
		std::copy(buffer_iterator_begin_block, buffer_iterator_end_block, block.begin());

		auto position = buffer_iterator_begin_block - buffer.begin();
		license_block_t license_block = std::make_shared<const LicenseBlock>(block, position, timeout);
		license_blocks.push_back(license_block);

		buffer_iterator_begin_block = buffer_iterator_end_block;
	};

	return license_blocks;
}
const license_block_t LicenseBlockManager::find_block(p_block_func_t function_checker) const {
	license_block_t found_block = nullptr;

	auto lambda = [&found_block, function_checker](const license_block_t block) mutable ->bool {
		auto function_check = std::bind(function_checker, block);
		if (function_check()) {
			found_block = block;
			return true;
		}
		return false;
	};
	std::find_if(_license_blocks.begin(), _license_blocks.end(), lambda);

	return found_block;
}
const license_block_t LicenseBlockManager::find_first_free_block(void) const {
	return find_block(&LicenseBlock::is_expired);
}
#pragma endregion Private
