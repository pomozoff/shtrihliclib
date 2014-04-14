
#include "stdafx.h"

#include "Granule.h"
#include "ProtectKey.h"

#pragma region Constructor Destructor
Granule::Granule(const std::string id, const protect_key_t protect_key) :
_id(id),
_protect_key(protect_key)
{
}
Granule::~Granule(void) {
}
#pragma endregion

#pragma region Accessors
void Granule::set_granule_nfr_date(bool is_granule_nfr_date) const {
	_is_granule_nfr_date = is_granule_nfr_date;
}
const bool Granule::is_granule_nfr_date(void) const {
	return _is_granule_nfr_date;
}
#pragma endregion

#pragma region KeyChecker Interface
const bool Granule::check(void) const {
	bool result = false;
	for (const auto& element : _check_methods) {
		result = result && element->check(shared_from_this());
		if (_protect_key->is_key_nfr() && is_granule_nfr_date()) {
			result = true;
		}
	}

	return result;
}
void Granule::logout(const bool forced_logout) const {
	return nullptr == _protect_key ? true : _protect_key->logout(forced_logout);
}
#pragma endregion

#pragma region IKeyChecker Interface
const bool Granule::is_base_key_available(const check_method_base_t check_method) const {
	return nullptr == _protect_key ? false : _protect_key->is_base_key_available(check_method);
}
const bool Granule::is_able_to_login(const check_method_login_t check_method) const {
	return nullptr == _protect_key ? false : _protect_key->is_able_to_login(check_method);
}
const bool Granule::is_same_memory(const check_method_memory_t check_method) const {
	bool result = false;

	if (nullptr == _protect_key) {
		return false;
	} else if (_read_memory_to_value) {
		_value = _protect_key->read_memory(check_method);
		result = _value.size() > 0;
	} else {
		_protect_key->is_same_memory(check_method);
	}

	if (_is_granule_nfr_date) {
		time_t nfr_end_date;
		if (2 == _value.size()) {
			nfr_end_date = make_unix_time_from_old_format(_value);
		} else {
			nfr_end_date = time(NULL);
		}
		_protect_key->set_nfr_end_date(nfr_end_date);
	}

	return false;
}
const bool Granule::logout_key(const check_method_login_t check_method) const {
	return nullptr == _protect_key ? true : _protect_key->logout_key(check_method);
}
#pragma endregion

#pragma region Private
const time_t Granule::make_unix_time_from_old_format(const value_t value) const {
	if (2 != value.size()) {
		return 0;
	}
	return value[0] * 256 + value[1];
}
#pragma endregion
