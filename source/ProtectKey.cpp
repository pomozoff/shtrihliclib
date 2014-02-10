
#include "stdafx.h"

#include "ProtectKey.h"
#include "Granule.h"

ProtectKey::ProtectKey(void) {
}
ProtectKey::~ProtectKey(void) {
	logout(true);
	m_granules.clear();
}

const std::unique_ptr<const ProtectKey> ProtectKey::create_key(const KeyType key_type) {
	std::unique_ptr<const ProtectKey> protect_key = nullptr;
	switch (key_type) {
		case KeyType::Base:
			protect_key = nullptr;
			break;
		case KeyType::HaspSL:
			protect_key = nullptr;
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
const std::shared_ptr<const IProtectKey> ProtectKey::find_key(const keys_t keys_list, const std::shared_ptr<IProtectKeyDelegate> key_delegate) {
	std::shared_ptr<const IProtectKey> protect_key = nullptr;
	for (const auto& element : keys_list) {
		element->set_max_check_number(1);
		element->m_key_delegate = nullptr;

		bool is_key_found = element->check();
		if (is_key_found) {
			element->check_granules();
			element->m_key_delegate = key_delegate;
		}

		element->logout_after_check();
		if (is_key_found) {
			protect_key = element;
			break;
		}
	}

	return protect_key;
}

const bool ProtectKey::is_key_nfr(void) const {
	return m_is_key_nfr;
}
const bool ProtectKey::check(void) const {
	bool result = false;
	std::shared_ptr<const ProtectKey> sp_this = shared_from_this();

	for (const auto& element : m_check_methods) {
		if (m_is_key_nfr && element->is_check_method_for_NFR()) {
			return true;
		}

		result = element->check(sp_this);
		m_is_key_nfr = result && element->is_check_method_for_NFR();

		if (!result && !element->is_check_method_for_NFR()) {
			break;
		}
	}

	return result;
}
void ProtectKey::check_granules(void) const {
	for (const auto& element : m_granules) {
		element->check();
	}
}
void ProtectKey::logout_after_check(void) const {
	if (m_logout_after_check) {
		logout(false);
	}
}

/* IKeyChecker Interface */
const bool ProtectKey::is_base_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const {
	return false;
}
const bool ProtectKey::is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const {
	return logout_key(checkMethod);
}
const bool ProtectKey::is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const {
	return false;
}
const bool ProtectKey::logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const {
	return false;
}
