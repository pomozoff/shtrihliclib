
#include "stdafx.h"

#include "IProtectKey.h"

#pragma region Constructor Destructor
IProtectKey::IProtectKey(void) {
}
IProtectKey::~IProtectKey(void) {
}
#pragma endregion

#pragma region Accessors
void IProtectKey::set_decrypt_method(const check_method_login_t decrypt_method) const {
	_decrypt_method = decrypt_method;
}
#pragma endregion
