
#include "stdafx.h"

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
const value_t LicenseBlock::create_block_as_buffer_from_hash(const size_t hash, const time_t time_logged_in) {
	value_t buffer(sizeof_data);

	byte_t* p_buffer_hash = &buffer[0];
	*p_buffer_hash = hash;

	byte_t* p_buffer_time = &buffer[sizeof_hash];
	*p_buffer_time = time_logged_in;

	size_t crc = hash_value(buffer);
	buffer.resize(sizeof_data + sizeof_hash);

	byte_t* p_buffer_crc = &buffer[sizeof_data];
	*p_buffer_crc = crc;

	return buffer;
}
const size_t LicenseBlock::hash_value(value_t buffer) {
	std::string hashed_string = R"()";
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(hashed_string));

	std::hash<std::string> hasher;
	return hasher(hashed_string);
}
