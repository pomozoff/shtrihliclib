
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
