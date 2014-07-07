
#include "stdafx.h"

#include "MockRealKey.h"

#pragma region Constructor Destructor
MockRealKey::MockRealKey(void) {
}
MockRealKey::~MockRealKey(void) {
}
#pragma endregion

#pragma region Protected
const bool MockRealKey::is_enabled(void) const {
	return _is_enabled;
}
void MockRealKey::set_enabled(const bool is_enabled) const {
	_is_enabled = is_enabled;
}
#pragma endregion
