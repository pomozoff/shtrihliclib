
#include "stdafx.h"

#include <iterator>
#include <ctime>

#include "LicenseBlock.h"
#include "ProtectKey.h"

#pragma region Constructor Destructor
LicenseBlock::LicenseBlock(const value_t block, const offset_t offset, const time_t timeout) :
_block(block),
_offset_in_manager(offset),
_timeout(timeout)
{
}
LicenseBlock::~LicenseBlock(void) {
}
#pragma endregion Constructor Destructor

#pragma region Public
const value_t LicenseBlock::block_from_string(const std::string session_id, const time_t time_logged_in) {
	std::hash<std::string> hasher;
	size_t hash = hasher(session_id);
	return block_from_hash(hash, time_logged_in);
}
const bool LicenseBlock::is_expired() const {
	return (!is_valid()) || (difftime(time(NULL), logged_in_time()) > _timeout);
}
const time_t LicenseBlock::logged_in_time() const {
	time_t logged_in = 0;
	if (!get_data_from_buffer_at_offset(_block, sizeof_hash, logged_in)) {
		return 0;
	}
	return logged_in;
}
const bool LicenseBlock::is_it_my_block(void) const {
	if (!is_valid()) {
		return false;
	}

	size_t block_id_hash = 0;
	if (!get_data_from_buffer_at_offset(_block, 0, block_id_hash)) {
		return false;
	}
	return block_id_hash == ProtectKey::session_id_hash();
}
void LicenseBlock::update_block(const time_t time) const {
	_block = block_from_hash(ProtectKey::session_id_hash(), time);
}
void LicenseBlock::make_expired(void) const {
	update_block(0);
}
#pragma endregion Public

#pragma region Accessors
const offset_t LicenseBlock::offset_in_manager(void) const {
	return _offset_in_manager;
}
const value_t& LicenseBlock::block(void) const {
	return _block;
}
#pragma endregion Accessors

#pragma region Private
template <typename T>
const bool LicenseBlock::place_data_to_buffer_at_offset(value_t& buffer, const offset_t offset, const T data) {
	if ((offset + sizeof data) > buffer.size()) {
		return false;
	}

	auto begin = static_cast<const byte_t*>(static_cast<const void*>(&data));
	auto end = static_cast<const byte_t*>(static_cast<const void*>(&data)) + sizeof data;

	std::copy(begin, end, buffer.begin() + offset);

	return true;
}
template <typename T>
const bool LicenseBlock::get_data_from_buffer_at_offset(const value_t buffer, const offset_t offset, T& data) {
	if ((offset + sizeof data) > buffer.size()) {
		return false;
	}

	auto p_data = static_cast<byte_t*>(static_cast<void*>(&data));
	auto begin = buffer.begin() + offset;
	auto end = buffer.begin() + offset + sizeof data;

	std::copy(begin, end, p_data);

	return true;
}
const value_t LicenseBlock::block_from_hash(const size_t hash, const time_t time_logged_in) {
	value_t buffer(sizeof_block);

	place_data_to_buffer_at_offset(buffer, 0, hash);
	place_data_to_buffer_at_offset(buffer, sizeof_hash, time_logged_in);

	size_t crc = hash_value(buffer, 0, sizeof_data);
	place_data_to_buffer_at_offset(buffer, sizeof_data, crc);

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
const bool LicenseBlock::is_valid() const {
	size_t block_hash = 0;
	if (!get_data_from_buffer_at_offset(_block, sizeof_data, block_hash)) {
		return false;
	}

	const size_t computed_hash = hash_value(_block, 0, sizeof_data);
	if (!computed_hash) {
		return false;
	}

	return computed_hash == block_hash;
}
#pragma endregion Private
