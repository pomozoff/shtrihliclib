
#include "stdafx.h"

#include "ProtectKeyRockeyLocal.h"

#pragma region Constructor Destructor
ProtectKeyRockeyLocal::ProtectKeyRockeyLocal(const real_key_rockey_t key)
	: ProtectKeyRockey(key, KeyType::RockeyLocal)
{
}
ProtectKeyRockeyLocal::~ProtectKeyRockeyLocal(void) {
}
#pragma endregion

#pragma region IKeyChecker Interface
const std::string ProtectKeyRockeyLocal::get_key_type(void) const {
	return "Rockey 4 Local";
}
#pragma endregion
