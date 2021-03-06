
#include "stdafx.h"

#include "Granule.h"
#include "ProtectKey.h"

#pragma region Constructor Destructor
Granule::Granule(const std::wstring id, const protect_key_weak_t protect_key) :
_name(id),
_protect_weak_key(protect_key)
{
}
Granule::~Granule(void) {
}
#pragma endregion

#pragma region Accessors
const std::wstring Granule::name(void) const {
	return _name;
}
void Granule::set_granule_nfr_date(bool is_granule_nfr_date) const {
	_is_granule_nfr_date = is_granule_nfr_date;
}
const bool Granule::is_granule_nfr_date(void) const {
	return _is_granule_nfr_date;
}
void Granule::set_read_memory_to_value(const bool read_memory_to_value) const {
	_read_memory_to_value = read_memory_to_value;
}
const bool Granule::read_memory_to_value(void) const {
	return _read_memory_to_value;
}
const value_t Granule::value(void) const {
	return _value;
}
#pragma endregion

#pragma region KeyChecker Interface
const bool Granule::check(void) const {
	bool result = _check_methods.size() > 0;
	for (auto&& element : _check_methods) {
		result = result && element->check(shared_from_this());
		auto _protect_key = _protect_weak_key.lock();
		if (_protect_key->is_key_nfr() && is_granule_nfr_date()) {
			result = true;
		}
	}
	return result;
}
void Granule::logout(const bool forced_logout) const {
	auto _protect_key = _protect_weak_key.lock();
	return nullptr == _protect_key ? true : _protect_key->logout(forced_logout);
}
const key_handle_t Granule::get_handle(const check_method_login_t check_method) const {
	auto _protect_key = _protect_weak_key.lock();
	return _protect_key->get_handle(check_method);
}
#pragma endregion

#pragma region IKeyChecker Interface
const bool Granule::is_base_key_available(const check_method_base_t check_method) const {
	auto _protect_key = _protect_weak_key.lock();
	return nullptr == _protect_key ? false : _protect_key->is_base_key_available(check_method);
}
const bool Granule::is_able_to_login(const check_method_login_t check_method) const {
	auto _protect_key = _protect_weak_key.lock();
	return nullptr == _protect_key ? false : _protect_key->is_able_to_login(check_method);
}
const bool Granule::is_same_memory(const check_method_memory_t check_method) const {
	bool result = false;
	auto _protect_key = _protect_weak_key.lock();
	if (nullptr == _protect_key) {
		return false;
	} else if (_read_memory_to_value) {
		_value = _protect_key->read_memory(check_method);
		result = _value.size() > 0;
	} else {
		result = _protect_key->is_same_memory(check_method);
	}
	if (_is_granule_nfr_date) {
		time_t nfr_end_date;
		if (2 == _value.size()) {
			nfr_end_date = make_unix_time_from_old_format(_value);
		} else {
			nfr_end_date = std::time(NULL);
		}
		_protect_key->set_nfr_end_date(nfr_end_date);
	}
	return result;
}
const bool Granule::logout_key(const check_method_login_t check_method) const {
	auto _protect_key = _protect_weak_key.lock();
	return nullptr == _protect_key ? true : _protect_key->logout_key(check_method);
}
#pragma endregion

#pragma region Private
const time_t Granule::make_unix_time_from_old_format(const value_t value) const {
	if (2 != value.size()) {
		return 0;
	}

	int days = value[0] * 256 + value[1];
	int delphi_delta_days = 25569;
	time_t seconds_in_day = 60 * 60 * 24;

	time_t timestamp = static_cast<time_t>(days - delphi_delta_days) * seconds_in_day;

	return timestamp;
}
#pragma endregion
