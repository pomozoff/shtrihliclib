
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

const rockey_long_t MockRealKeyRockeyLocal::prepared_feature_id(const rockey_feature_t feature_id) const {
	return feature_id + 0x10000;
}
