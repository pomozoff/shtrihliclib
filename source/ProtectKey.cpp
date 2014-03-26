
#include "stdafx.h"

#include <iterator>

#include "ProtectKey.h"
#include "Granule.h"
#include "ProtectKeyHaspSL.h"
#include "Platform.h"
#include "RealKeyHaspSL.h"

#pragma region Constants
static const platform_t _platform = Platform::platform();
static std::string _session_id = R"()";
static size_t _session_id_hash = 0;
#pragma endregion Constants

#pragma region Constructor Destructor
ProtectKey::ProtectKey(void) {
}
ProtectKey::~ProtectKey(void) {
	logout(true);
	_granules.clear();
}
#pragma endregion Constructor Destructor

#pragma region Public
const std::string ProtectKey::session_id(void) {
	if (_session_id.empty()) {
		_session_id = _platform->computer_name() + _platform->user_name();
	}
	return _session_id;
}
const size_t ProtectKey::session_id_hash(void) {
	if (_session_id_hash == 0) {
		std::hash<std::string> hasher;
		_session_id_hash = hasher(session_id());
	}
	return _session_id_hash;
const size_t ProtectKey::hash_from_session_id(const std::string session_id) {
	std::hash<std::string> hasher;
	return hasher(session_id);
}

const protect_key_t ProtectKey::create_key(const KeyType key_type) {
	protect_key_t protect_key = nullptr;
	switch (key_type) {
		case KeyType::Base:
			protect_key = nullptr;
			break;
		case KeyType::HaspSL: {
				auto key = std::make_shared<const RealKeyHaspSL>();
				protect_key = std::make_shared<const ProtectKeyHaspSL>(key);
			}
			break;
		case KeyType::HaspHLLocal:
			protect_key = nullptr;
			break;
		case KeyType::HaspHLNet:
			protect_key = nullptr;
			break;
		case KeyType::RockeyLocal:
			protect_key = nullptr;
			break;
		case KeyType::RockeyNet:
			protect_key = nullptr;
			break;
		case KeyType::FileMapped:
			protect_key = nullptr;
			break;
		default:
			break;
	}
	return protect_key;
}

const iprotect_key_t ProtectKey::find_key(const protect_keys_t& keys_list, const iprotect_key_delegate_t key_delegate) {
	iprotect_key_t protect_key = nullptr;
	for (const auto& element : keys_list) {
		element->set_max_check_number(1);
		element->_key_delegate = nullptr;

		bool is_key_found = element->check();
		if (is_key_found) {
			element->check_granules();
			element->_key_delegate = key_delegate;
		}

		element->try_to_logout();
		if (is_key_found) {
			protect_key = element;
			break;
		}
	}
	return protect_key;
}
const bool ProtectKey::copy_block_to_buffer(const value_t& source, value_t& destination, const size_t length, const offset_t source_offset, const offset_t destination_offset) {
	if (source_offset >= source.size()
		|| destination_offset >= destination.size()
		|| (source_offset + length) > source.size()
		|| (destination_offset + length) > destination.size()) {
		return false;
	}

	auto source_iterator_begin = source.begin() + source_offset;
	auto source_iterator_end = source.begin() + source_offset + length;
	auto destination_iterator = destination.begin() + destination_offset;

	std::copy(source_iterator_begin, source_iterator_end, std::inserter(destination, destination_iterator));
	
	return true;
}
#pragma endregion Public

#pragma region Accessors
const bool ProtectKey::logout_after_check(void) const {
	return _logout_after_check;
}
void ProtectKey::set_logout_after_check(const bool logout_after_check) const {
	_logout_after_check = logout_after_check;
}
const time_t ProtectKey::nfr_end_date(void) const {
	return _nfr_end_date;
}
void ProtectKey::set_nfr_end_date(const time_t nfr_end_date) const {
	_nfr_end_date = nfr_end_date;
}
#pragma endregion Accessors

#pragma region IProtectKey Interface
const bool ProtectKey::check_license(void) const {
	if (_is_key_nfr) {
		return false;
	}
	bool result = check_license_with_methods() || recheck_key();

	return result;
}
const bool ProtectKey::is_key_nfr(void) const {
	return _is_key_nfr;
}
const bool ProtectKey::is_key_base(void) const {
	return _is_key_base;
}
#pragma endregion IProtectKey Interface

#pragma region KeyChecker Interface
const bool ProtectKey::check(void) const {
	bool result = false;
	protect_key_t sp_this = shared_from_this();

	for (const auto& element : _check_methods) {
		if (_is_key_nfr && element->is_check_method_for_nfr()) {
			return true;
		}

		result = element->check(sp_this);
		_is_key_nfr = result && element->is_check_method_for_nfr();

		if (!result && !element->is_check_method_for_nfr()) {
			break;
		}
	}

	return result;
}
#pragma endregion KeyChecker Interface

#pragma region IKeyChecker Interface
const bool ProtectKey::is_base_key_available(const check_method_base_t check_method) const {
	return false;
}
const bool ProtectKey::is_able_to_login(const check_method_login_t check_method) const {
	return logout_key(check_method);
}
const bool ProtectKey::is_same_memory(const check_method_memory_t check_method) const {
	return false;
}
const bool ProtectKey::logout_key(const check_method_login_t check_method) const {
	return false;
}
#pragma endregion IKeyChecker Interface

#pragma region Protected
void ProtectKey::check_granules(void) const {
	for (const auto& element : _granules) {
		element->check();
	}
}
void ProtectKey::try_to_logout(void) const {
	if (_logout_after_check) {
		logout(false);
	}
}
#pragma endregion Protected

#pragma region Private
const bool ProtectKey::check_license_with_methods(void) const {
	bool result = false;
	protect_key_t sp_this = shared_from_this();

	for (const auto& element : _check_methods) {
		if (!element->is_check_method_for_license()) {
			continue;
		}
		result = element->check(sp_this);
		if (!result) {
			break;
		}
	}
	return result;
}
const bool ProtectKey::recheck_key(void) const {
	iprotect_key_delegate_t temp_delegate = _key_delegate;
	_key_delegate = nullptr;

	bool result = check();
	if (result) {
		check_granules();
		_key_delegate = temp_delegate;
	}
	try_to_logout();

	return result;
}
void ProtectKey::add_feature(const feature_t feature) const {
	_features.push_back(feature);
}
#pragma endregion Private
