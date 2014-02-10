
#pragma once

#include "IGranulesManager.h"

class IProtectKey : public IGranulesManager {
	public:
		IProtectKey(void);
		virtual ~IProtectKey(void);

		virtual const bool is_key_nfr(void) const = 0;
};
