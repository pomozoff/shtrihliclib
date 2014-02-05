
#pragma once

#include "IProtectKey.h"
#include "KeyChecker.h"

class ProtectKey : public IProtectKey, KeyChecker {
	public:
		ProtectKey(void);
		~ProtectKey(void);
};
