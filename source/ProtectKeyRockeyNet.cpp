
#include "stdafx.h"

#include "ProtectKeyRockeyNet.h"

#pragma region Constructor Destructor
ProtectKeyRockeyNet::ProtectKeyRockeyNet(const real_key_rockey_t key)
	: ProtectKeyRockey(key, KeyType::RockeyNet)
{

}
ProtectKeyRockeyNet::~ProtectKeyRockeyNet(void) {
}
#pragma endregion
