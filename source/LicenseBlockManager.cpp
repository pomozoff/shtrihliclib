
#include "stdafx.h"

#include "LicenseBlockManager.h"

LicenseBlockManager::LicenseBlockManager(const value_t buffer, const time_t timeout, const size_t licenses_amount) :
_timeout(timeout),
_licenses_amount(licenses_amount),
_license_blocks(license_blocks_from_buffer(buffer))
{
}
LicenseBlockManager::~LicenseBlockManager(void) {
}
