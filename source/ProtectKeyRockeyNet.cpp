
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

#pragma region IKeyChecker Interface
const std::string ProtectKeyRockeyNet::get_key_type(void) const {
	std::string key_type = "Rockey 4 Net";
	if (is_key_nfr()) {
		key_type.append(" NFR");
	}
	return key_type;
}
#pragma endregion
