
#include "stdafx.h"

#include <iterator>

#include "LicenseBlock.h"

LicenseBlock::LicenseBlock(const value_t buffer, const offset_t offset, const time_t timeout) :
_buffer(buffer),
_offset(offset),
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
	if (offset >= buffer.size() || (offset + sizeof data) > buffer.size()) {
		return false;
	}

	auto begin = static_cast<const byte_t*>(static_cast<const void*>(&data));
	auto end   = static_cast<const byte_t*>(static_cast<const void*>(&data)) + sizeof data;

	std::copy(begin, end, &buffer[offset]);

	return true;
}
const value_t LicenseBlock::create_block_as_buffer_from_hash(const size_t hash, const time_t time_logged_in) {
	value_t buffer(sizeof_data);

	place_data_to_buffer_at_offset(hash, buffer, 0);
	place_data_to_buffer_at_offset(time_logged_in, buffer, sizeof_hash);

	size_t crc = hash_value(buffer);
	buffer.resize(sizeof_data + sizeof_hash);

	place_data_to_buffer_at_offset(crc, buffer, sizeof_data);

	return buffer;
}
const size_t LicenseBlock::hash_value(value_t buffer) {
	std::string hashed_string = R"()";
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(hashed_string));

	std::hash<std::string> hasher;
	return hasher(hashed_string);
}
