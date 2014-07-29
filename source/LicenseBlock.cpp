
#include "stdafx.h"

#include <iterator>
#include <ctime>

#include "LicenseBlock.h"
#include "ProtectKey.h"

#pragma region Constructor Destructor
LicenseBlock::LicenseBlock(const value_t block, const offset_t offset, const time_t loggedin_period_seconds, const size_t session_id_hash) :
_block(block),
_offset_in_manager(offset),
_loggedin_period_seconds(loggedin_period_seconds),
_current_session_id_hash(session_id_hash)
{
}
LicenseBlock::~LicenseBlock(void) {
}
#pragma endregion

#pragma region Public
const value_t LicenseBlock::block_from_string(const std::wstring session_id, const time_t loggedin_until_value) {
	auto hash = ProtectKey::hash_from_session_id(session_id);
	return block_from_hash(hash, loggedin_until_value);
}

const size_t LicenseBlock::position_in_manager(void) const {
	return _offset_in_manager / sizeof_block;
}
const bool LicenseBlock::is_expired(void) const {
	return (!is_valid()) || (std::time(NULL) > loggedin_until());
}
const bool LicenseBlock::is_it_my_block(void) const {
	if (!is_valid()) {
		return false;
	}

	size_t block_id_hash = 0;
	if (!get_data_from_buffer_at_offset(_block, 0, block_id_hash)) {
		return false;
	}
	return block_id_hash == _current_session_id_hash;
}
void LicenseBlock::update_block(const time_t time) const {
	_block = block_from_hash(_current_session_id_hash, time);
}
void LicenseBlock::make_expired(void) const {
	update_block(std::time(NULL) - _loggedin_period_seconds);
}
#pragma endregion

#pragma region Accessors
const offset_t LicenseBlock::offset_in_manager(void) const {
	return _offset_in_manager;
}
const value_t& LicenseBlock::block(void) const {
	return _block;
}
const time_t LicenseBlock::loggedin_period_seconds(void) const {
	return _loggedin_period_seconds;
}
const time_t LicenseBlock::loggedin_until(void) const {
	time_t loggedin_until_value = 0;
	if (!get_data_from_buffer_at_offset(_block, sizeof_hash, loggedin_until_value)) {
		return 0;
	}
	return loggedin_until_value;
}
#pragma endregion

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
const value_t LicenseBlock::block_from_hash(const size_t hash, const time_t loggedin_until_value) {
	value_t buffer(sizeof_block);

	place_data_to_buffer_at_offset(buffer, 0, hash);
	place_data_to_buffer_at_offset(buffer, sizeof_hash, loggedin_until_value);

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
#pragma endregion
