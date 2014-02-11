
#include "stdafx.h"

#include "Granule.h"
#include "ProtectKey.h"

Granule::Granule(const std::string id, const std::shared_ptr<const ProtectKey> protect_key) :
_id(id),
_protect_key(protect_key)
{
}
Granule::~Granule(void) {
}

const bool Granule::check(void) const {
	bool result = false;
	std::shared_ptr<const Granule> sp_this = shared_from_this();

	for (const auto& element : _check_methods) {
		result = result && element->check(sp_this);
		if (_protect_key->is_key_nfr() && is_granule_nfr_date()) {
			result = true;
		}
	}

	return result;
}

void Granule::set_granule_nfr_date(bool is_granule_nfr_date) {
	_is_granule_nfr_date = is_granule_nfr_date;
}
const bool Granule::is_granule_nfr_date(void) const {
	return _is_granule_nfr_date;
}
