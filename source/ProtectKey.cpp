
#include "stdafx.h"

#include <iterator>

#include <openssl/aes.h>
#include <openssl/rand.h>

#include "ProtectKey.h"
#include "Granule.h"
#include "ProtectKeyHaspSL.h"
#include "Platform.h"
#include "RealKeyHaspSL.h"

static const uint16_t AES_key_length = 256;

#pragma region Constructor Destructor
ProtectKey::ProtectKey(const size_t session_id_hash) :
_session_id_hash(session_id_hash),
_key_delegate(NULL)
{
}
ProtectKey::~ProtectKey(void) {
	_granules.clear();
}
#pragma endregion

#pragma region Public
const std::wstring ProtectKey::session_id(platform_t platform) {
	auto session_id = platform->session_id();
	return session_id;
}
const size_t ProtectKey::hash_from_session_id(const std::wstring session_id) {
	std::hash<std::wstring> hasher;
	return hasher(session_id);
}
const protect_key_t ProtectKey::create_key(const KeyType key_type, const platform_t platform) {
	return create_key(key_type, platform->session_id());
}

const iprotect_key_weak_t ProtectKey::find_key(const protect_keys_t& keys_list, IProtectKeyDelegate& key_delegate) {
	iprotect_key_weak_t iprotect_key;
	for (const auto& element : keys_list) {
		element->set_max_check_number(1);
		element->_key_delegate = NULL;

		bool is_key_found = element->check();
		if (is_key_found) {
			element->check_granules();
			element->_key_delegate = &key_delegate;
		}

		element->try_to_logout();
		if (is_key_found) {
			iprotect_key = element;
			break;
		}
	}
	return iprotect_key;
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

	std::move(source_iterator_begin, source_iterator_end, destination_iterator);
	
	return true;
}
const granule_t ProtectKey::create_granule(const std::wstring id) const {
	auto granule = std::make_shared<const Granule>(id, shared_from_this());
	_granules.push_back(granule);
	return granule;
}
void ProtectKey::removeGranules(void) const {
	_granules.clear();
}
#pragma endregion

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
#pragma endregion

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
void ProtectKey::decrypt(const byte_t* encoded_buffer, byte_t* iv_dec, byte_t* decoded_buffer, const size_t decoded_length) const {
	std::string aes_key_str = "XHQEwGsbezV1ngPFfmLzNhRUy7nTapOj";

	// buffers for encryption and decryption
	const size_t encslength = ((decoded_length + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
	byte_t* internal_decoded_buffer = new byte_t[encslength];

	AES_KEY dec_key;
	AES_set_decrypt_key(reinterpret_cast<const byte_t*>(aes_key_str.data()), AES_key_length, &dec_key);
	AES_cbc_encrypt(encoded_buffer, internal_decoded_buffer, encslength, &dec_key, iv_dec, AES_DECRYPT);

	std::memcpy(decoded_buffer, internal_decoded_buffer, decoded_length);
	delete[] internal_decoded_buffer;
}
#pragma endregion

#pragma region KeyChecker Interface
const bool ProtectKey::check(void) const {
	bool result = false;
	for (const auto& element : _check_methods) {
		bool is_check_nfr_true = element->is_check_method_for_nfr();
		if (_is_key_nfr && is_check_nfr_true) {
			return true;
		}
		result = element->check(shared_from_this());
		_is_key_nfr = result && is_check_nfr_true;

		if (!result && !is_check_nfr_true) {
			break;
		}
	}
	return result;
}
#pragma endregion

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
#pragma endregion

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
const protect_key_t ProtectKey::create_key(const KeyType key_type, const std::wstring session_id) {
	protect_key_t protect_key = nullptr;
	switch (key_type) {
	case KeyType::Base:
		protect_key = nullptr;
		break;
	case KeyType::HaspSL: {
		auto key = std::make_shared<const RealKeyHaspSL>();
		protect_key = std::make_shared<const ProtectKeyHaspSL>(key, hash_from_session_id(session_id));
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
#pragma endregion

#pragma region Private
const bool ProtectKey::check_license_with_methods(void) const {
	bool result = false;
	for (const auto& element : _check_methods) {
		if (!element->is_check_method_for_license()) {
			continue;
		}
		result = element->check(shared_from_this());
		if (!result) {
			break;
		}
	}
	return result;
}
const bool ProtectKey::recheck_key(void) const {
	auto& temp_delegate = _key_delegate;
	_key_delegate = NULL;

	bool result = check();
	if (result) {
		check_granules();
		_key_delegate = temp_delegate;
	}
	try_to_logout();

	return result;
}
#pragma endregion
