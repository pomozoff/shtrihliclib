
#include "stdafx.h"

#include <iterator>
#include <algorithm>
#include <functional>

#include <openssl/aes.h>
#include <openssl/rand.h>

#include "Platform.h"
#include "ProtectKey.h"
#include "Granule.h"

#include "ProtectKeyHaspSL.h"
#include "RealKeyHaspSL.h"

#include "ProtectKeyRockeyLocal.h"
#include "ProtectKeyRockeyNet.h"

#include "RealKeyRockeyLocal.h"
#include "RealKeyRockeyNet.h"

static const uint16_t AES_key_length = 256;
static const std::string AES_key_str = "XHQEwGsbezV1ngPFfmLzNhRUy7nTapOj";

#pragma region Constructor Destructor
ProtectKey::ProtectKey(const KeyType keytype)
	: _key_delegate(NULL)
#ifdef _DEBUG
	, _license_timeout(10)  // поиск ключа каждые 10 секунд
#else
	, _license_timeout(60 * 30)  // поиск ключа каждые полчаса
#endif
	, _keytype(keytype)
{
}
ProtectKey::~ProtectKey(void) {
	_granules.clear();
	logout(true);
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
void ProtectKey::call_delegate(bool isSuccess) const {
	if (_key_delegate) {
		_key_delegate->did_check_protect_key(isSuccess);
	}
}
const iprotect_key_weak_t ProtectKey::find_key(const protect_keys_t& keys_list, IProtectKeyDelegate& key_delegate) {
	iprotect_key_weak_t iprotect_key;

	auto for_every_object_in_container = [](const std::vector<const check_method_t>& container,
		const check_number_t&& value,
		member_function_t<CheckMethod, void, const check_number_t> function)
	{
		for (auto&& object : container) {
			std::bind(function, object, value)();
		}
	};

	for (auto&& protect_key : keys_list) {
		// Установить максимальное неудачных попыток в минимальное значение
		// т.к. поиск ключа должен происходить всего один раз
		for_every_object_in_container(protect_key->_check_methods,
			1,
			&CheckMethod::set_max_check_number);

		// Сбрасываем текущее значение попыток поиска лицензий
		// т.к. ищем новый ключ, старое значение уже не нужно
		for_every_object_in_container(protect_key->_check_methods,
			0,
			&CheckMethod::set_current_check_number);

		// При поиске ключа не надо оповещать делегата
		protect_key->_key_delegate = NULL;

		// Ищем ключ
		bool is_key_found = protect_key->check();
		if (is_key_found) {
			protect_key->check_granules();
			protect_key->_key_delegate = &key_delegate;
		}

		// Отлогиниваемся если необходимо
		protect_key->try_to_logout();

		// Установить дефолтное максимальное значение неудачных попыток взад
		// чтобы поиск лицензии имел возможность несколько раз неудачно завершиться
		for_every_object_in_container(protect_key->_check_methods,
			protect_key->max_check_number(),
			&CheckMethod::set_max_check_number);

		if (is_key_found) {
			iprotect_key = protect_key;
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
const granule_t ProtectKey::create_granule(const std::wstring name) const {
	auto granule = std::make_shared<const Granule>(name, shared_from_this());
	_granules.push_back(granule);
	return granule;
}
void ProtectKey::removeGranules(void) const {
	_granules.clear();
}
const granule_t ProtectKey::granule_with_name(const std::wstring& granule_name) const {
	auto iterator = std::find_if(_granules.begin(), _granules.end(), [&granule_name] (const granule_t& granule) {
		return granule->name() == granule_name;
	});
	return iterator != _granules.end() ? *iterator : nullptr;
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
	bool result = check_license_with_methods() || recheck_key();
	return result;
}
const bool ProtectKey::is_key_nfr(void) const {
	return _is_key_nfr;
}
const bool ProtectKey::is_key_base(void) const {
	return _is_key_base;
}
const time_t ProtectKey::check_license_timeout(void) const {
	return _license_timeout;
}
void ProtectKey::encrypt(const byte_t* input_buffer, const size_t input_length, byte_t** iv_enc, size_t& iv_length, byte_t** encrypted_buffer, size_t& encrypted_length) const {
	// buffers for encryption and decryption
	encrypted_length = ((input_length + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
	*encrypted_buffer = new byte_t[encrypted_length];

	byte_t* internal_iv_enc = new byte_t[AES_BLOCK_SIZE];
	RAND_bytes(internal_iv_enc, AES_BLOCK_SIZE);

	*iv_enc = new byte_t[AES_BLOCK_SIZE];
	std::memcpy(*iv_enc, internal_iv_enc, AES_BLOCK_SIZE);

	iv_length = AES_BLOCK_SIZE;

	AES_KEY enc_key;
	AES_set_encrypt_key(reinterpret_cast<const byte_t*>(AES_key_str.data()), AES_key_length, &enc_key);
	AES_cbc_encrypt(input_buffer, *encrypted_buffer, encrypted_length, &enc_key, internal_iv_enc, AES_ENCRYPT);

	delete[] internal_iv_enc;
}
void ProtectKey::decrypt(const byte_t* encrypted_buffer, const size_t encrypted_length, byte_t* iv_dec, byte_t** decrypted_buffer) const {
	*decrypted_buffer = new byte_t[encrypted_length];
	AES_KEY dec_key;
	AES_set_decrypt_key(reinterpret_cast<const byte_t*>(AES_key_str.data()), AES_key_length, &dec_key);
	AES_cbc_encrypt(encrypted_buffer, *decrypted_buffer, encrypted_length, &dec_key, iv_dec, AES_DECRYPT);
}
#pragma endregion

#pragma region KeyChecker Interface
const bool ProtectKey::check(void) const {
	bool result = false;
	bool is_check_nfr_true = false;
	for (auto&& element : _check_methods) {
		if (_is_key_nfr && is_check_nfr_true) {
			return true;
		}
		is_check_nfr_true = element->is_check_method_for_nfr();
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
	return KeyChecker::is_able_to_login(check_method);
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
	for (auto&& element : _granules) {
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
			auto real_key = std::make_shared<const RealKeyHaspSL>();
			protect_key = std::make_shared<const ProtectKeyHaspSL>(real_key, hash_from_session_id(session_id));
		}
		break;
	case KeyType::HaspHLLocal:
		protect_key = nullptr;
		break;
	case KeyType::HaspHLNet:
		protect_key = nullptr;
		break;
	case KeyType::RockeyLocal: {
			auto real_key = std::make_shared<const RealKeyRockeyLocal>();
			protect_key = std::make_shared<const ProtectKeyRockeyLocal>(real_key);
		}
		break;
	case KeyType::RockeyNet: {
			auto real_key = std::make_shared<const RealKeyRockeyNet>((char*)NULL);
			protect_key = std::make_shared<const ProtectKeyRockeyNet>(real_key);
		}
		break;
	case KeyType::FileMapped:
		protect_key = nullptr;
		break;
	default:
		break;
	}
	return protect_key;
}
const time_t ProtectKey::get_nfr_end_date(void) const {
	return _nfr_end_date;
}
#pragma endregion

#pragma region Private
const bool ProtectKey::check_license_with_methods(void) const {
	bool result = false;
	for (auto&& element : _check_methods) {
		if (   (_is_key_nfr  && !element->is_check_method_for_nfr())
			|| (!_is_key_nfr && !element->is_check_method_for_license()) ) {
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
