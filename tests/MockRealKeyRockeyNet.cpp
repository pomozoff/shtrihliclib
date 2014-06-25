
#include "stdafx.h"

#include "MockRealKeyRockeyNet.h"

#pragma region Constructor Destructor
MockRealKeyRockeyNet::MockRealKeyRockeyNet(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory)
	: MockRealKeyRockey(feature_id, check_methods_memory)
{
}
MockRealKeyRockeyNet::~MockRealKeyRockeyNet() {
}
#pragma endregion

const rockey_long_t MockRealKeyRockeyNet::prepared_feature_id(const rockey_feature_t feature_id) const {
	return feature_id + 0x10000;
}
const size_t MockRealKeyRockeyNet::max_memory_size(void) const {
	return _memory_size;
}
