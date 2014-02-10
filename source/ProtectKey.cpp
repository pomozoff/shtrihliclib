
#include "stdafx.h"

#include "ProtectKey.h"

ProtectKey::ProtectKey(void) {
}
ProtectKey::~ProtectKey(void) {
	logout();
	m_granules.clear();
}

const bool ProtectKey::check(void) const {
	return false;
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

