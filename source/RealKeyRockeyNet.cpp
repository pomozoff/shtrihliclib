
#include "stdafx.h"

#include "RealKeyRockeyNet.h"

#pragma region Constructor Destructor
RealKeyRockeyNet::RealKeyRockeyNet(void)
	: _is_terminal_mode(is_terminal_mode_detected())
{
}
RealKeyRockeyNet::~RealKeyRockeyNet(void) {
}
#pragma endregion

#pragma region Protected
const rockey_long_t RealKeyRockeyNet::prepared_feature_id(const rockey_feature_t feature_id) const {
	return feature_id + _is_terminal_mode ? 0 : 0x10000;
}
#pragma endregion

#pragma region Private
const bool RealKeyRockeyNet::is_terminal_mode_detected(void) const {
	return false;
}
#pragma endregion
