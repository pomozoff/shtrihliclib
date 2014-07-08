
#include "stdafx.h"

#include "MockRealKeyRockeyNet.h"

#pragma region Constructor Destructor
MockRealKeyRockeyNet::MockRealKeyRockeyNet(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory, const bool is_key_nfr)
	: MockRealKeyRockey(feature_id, check_methods_memory)
{
	set_is_key_nfr(is_key_nfr);
}
MockRealKeyRockeyNet::~MockRealKeyRockeyNet() {
}
#pragma endregion

#pragma region Public
void MockRealKeyRockeyNet::set_licenses_amount(const size_t amount) const {
	set_max_logins_amount(amount);
}
#pragma endregion

#pragma region Protected
const size_t MockRealKeyRockeyNet::max_memory_size(void) const {
	return _memory_size;
}
const rockey_long_t MockRealKeyRockeyNet::prepared_feature_id(const rockey_feature_t feature_id) const {
	return feature_id + 0x10000;
}
const uint16_t MockRealKeyRockeyNet::call_rockey(uint16_t function, uint16_t* handle, uint32_t* lp1, uint32_t* lp2, uint16_t* p1, uint16_t* p2, uint16_t* p3, uint16_t* p4, uint8_t* buffer) const {
	return ERR_NO_ROCKEY;
}
#pragma endregion
