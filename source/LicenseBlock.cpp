
#include "stdafx.h"

#include <iterator>
#include <ctime>

#include "LicenseBlock.h"

LicenseBlock::LicenseBlock(const value_t block, const offset_t offset, const time_t timeout) :
_block(block),
_offset_in_manager(offset),
_timeout(timeout)
{
}
LicenseBlock::~LicenseBlock(void) {
}

const value_t LicenseBlock::create_block_as_buffer_from_string(const std::string session_id, const time_t time_logged_in) {
	std::hash<std::string> hasher;
	size_t hash = hasher(session_id);
	return create_block_as_buffer_from_hash(hash, time_logged_in);
}

/* Private */
template <typename T>
const bool LicenseBlock::place_data_to_buffer_at_offset(const T data, value_t& buffer, const offset_t offset) {
	if ((offset + sizeof data) > buffer.size()) {
		return false;
	}

	auto begin = static_cast<const byte_t*>(static_cast<const void*>(&data));
	auto end   = static_cast<const byte_t*>(static_cast<const void*>(&data)) + sizeof data;

	std::copy(begin, end, &buffer[offset]);

	return true;
}
template <typename T>
const bool LicenseBlock::get_data_from_buffer_at_offset(T& data, const value_t buffer, const offset_t offset) {
	if ((offset + sizeof data) > buffer.size()) {
		return false;
	}

	auto p_data = static_cast<byte_t*>(static_cast<void*>(&data));
	auto begin = buffer.begin() + offset;
	auto end = buffer.begin() + offset + sizeof data;

	std::copy(begin, end, p_data);

	return true;
}
const value_t LicenseBlock::create_block_as_buffer_from_hash(const size_t hash, const time_t time_logged_in) {
	value_t buffer(sizeof_block);

	place_data_to_buffer_at_offset(hash, buffer, 0);
	place_data_to_buffer_at_offset(time_logged_in, buffer, sizeof_hash);

	size_t crc = hash_value(buffer, 0, sizeof_data);
	place_data_to_buffer_at_offset(crc, buffer, sizeof_data);

	return buffer;
}
const size_t LicenseBlock::hash_value(const value_t buffer, const offset_t offset, const size_t size) {
	std::string hashed_string = R"()";
	if ((offset + size) > buffer.size()) {
		return 0;
	}

	std::copy(buffer.begin(), buffer.begin() + size, std::back_inserter(hashed_string));

	std::hash<std::string> hasher;
	return hasher(hashed_string);
}
const time_t LicenseBlock::logged_in_time() const {
	time_t logged_in = 0;
	if (!get_data_from_buffer_at_offset(logged_in, _block, sizeof_hash)) {
		return 0;
	}
	return logged_in;
}
