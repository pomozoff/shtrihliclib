
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
#pragma endregion
