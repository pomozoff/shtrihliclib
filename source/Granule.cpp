
#include "stdafx.h"

#include "Granule.h"
#include "ProtectKey.h"

Granule::Granule(const std::string id, const std::shared_ptr<const ProtectKey> protect_key) :
m_id(id),
m_protect_key(protect_key)
{
}
Granule::~Granule(void) {
}

const bool Granule::check(void) const {
	bool result = false;
	std::shared_ptr<const Granule> sp_this = shared_from_this();

	for (const auto& element : m_check_methods) {
		result = result && element->check(sp_this);
		if (m_protect_key->is_key_nfr() && is_granule_nfr_date()) {
			result = true;
		}
	}

	return result;
}

void Granule::set_granule_nfr_date(bool is_granule_nfr_date) {
	m_is_granule_nfr_date = is_granule_nfr_date;
}
const bool Granule::is_granule_nfr_date(void) const {
	return m_is_granule_nfr_date;
}
