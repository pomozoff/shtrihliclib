
#include "stdafx.h"

#include "ProtectKey.h"

ProtectKey::ProtectKey(void) {
}
ProtectKey::~ProtectKey(void) {
	logout();
	m_granules.clear();
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
