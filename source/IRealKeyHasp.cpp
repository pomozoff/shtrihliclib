
#include "stdafx.h"

#include "IRealKeyHasp.h"

#pragma region Constructor Destructor
IRealKeyHasp::IRealKeyHasp(void) {
}
IRealKeyHasp::~IRealKeyHasp(void) {
}
#pragma endregion

#pragma region Accessors
const hasp_status_t IRealKeyHasp::last_status(void) const {
	return _last_status;
}
#pragma endregion
