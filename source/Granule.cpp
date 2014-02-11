﻿
#include "stdafx.h"

#include "Granule.h"
#include "ProtectKey.h"

Granule::Granule(const std::string id, const protect_key_t protect_key) :
_id(id),
_protect_key(protect_key)
{
}
Granule::~Granule(void) {
}

/* KeyChecker Interface */
const bool Granule::check(void) const {
	bool result = false;
	granule_t sp_this = shared_from_this();

	for (const auto& element : _check_methods) {
		result = result && element->check(sp_this);
		if (_protect_key->is_key_nfr() && is_granule_nfr_date()) {
			result = true;
		}
	}

	return result;
}

/* Properties */
void Granule::set_granule_nfr_date(bool is_granule_nfr_date) {
	_is_granule_nfr_date = is_granule_nfr_date;
}
const bool Granule::is_granule_nfr_date(void) const {
	return _is_granule_nfr_date;
}

/* IKeyChecker Interface */
const bool Granule::is_base_key_available(const check_method_base_t checkMethod) const {
	return nullptr == _protect_key ? false : _protect_key->is_base_key_available(checkMethod);
}
const bool Granule::is_able_to_login(const check_method_login_t checkMethod) const {
	return nullptr == _protect_key ? false : _protect_key->is_able_to_login(checkMethod);
}
const bool Granule::is_same_memory(const check_method_memory_t checkMethod) const {
	bool result = false;

	if (nullptr == _protect_key) {
		return false;
	} else if (_read_memory_to_value) {
		_value = _protect_key->read_memory(checkMethod);
		result = _value.size() > 0;
	} else {
		_protect_key->is_same_memory(checkMethod);
	}

	if (_is_granule_nfr_date) {
		if (2 == _value.size()) {

		}
	}

	return false;
}
const bool Granule::logout_key(const check_method_login_t checkMethod) const {
	return nullptr == _protect_key ? false : _protect_key->logout_key(checkMethod);
}
