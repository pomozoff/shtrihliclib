
#include "stdafx.h"

#include "RealKeyRockeyLocal.h"

#pragma region Constructor Destructor
RealKeyRockeyLocal::RealKeyRockeyLocal(void) {
}
RealKeyRockeyLocal::~RealKeyRockeyLocal(void) {
}
#pragma endregion

#pragma region Protected
const size_t RealKeyRockeyLocal::max_memory_size(void) const {
	return _memory_size;
}
const rockey_long_t RealKeyRockeyLocal::prepared_feature_id(const rockey_feature_t feature_id) const {
	return feature_id + 0x10000;
}
const uint16_t RealKeyRockeyLocal::call_rockey(uint16_t function, uint16_t* handle, uint32_t* lp1, uint32_t* lp2, uint16_t* p1, uint16_t* p2, uint16_t* p3, uint16_t* p4, uint8_t* buffer) const {
	return Rockey(function, handle, lp1, lp2, p1, p2, p3, p4, buffer);
}
#pragma endregion
