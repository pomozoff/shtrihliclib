
#include "stdafx.h"

#include "MockRealKeyRockeyLocal.h"

#pragma region Constructor Destructor
MockRealKeyRockeyLocal::MockRealKeyRockeyLocal(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory)
	: MockRealKeyRockey(feature_id, check_methods_memory)
{
}
MockRealKeyRockeyLocal::~MockRealKeyRockeyLocal() {
}
#pragma endregion

#pragma region Protected
const size_t MockRealKeyRockeyLocal::max_memory_size(void) const {
	return _memory_size;
}
const rockey_long_t MockRealKeyRockeyLocal::prepared_feature_id(const rockey_feature_t feature_id) const {
	return feature_id + 0x10000;
}
const uint16_t MockRealKeyRockeyLocal::call_rockey(uint16_t function, uint16_t* handle, uint32_t* lp1, uint32_t* lp2, uint16_t* p1, uint16_t* p2, uint16_t* p3, uint16_t* p4, uint8_t* buffer) const {
	return ERR_NO_ROCKEY;
}
#pragma endregion
