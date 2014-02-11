
#pragma once

#include "IGranulesManager.h"

class IProtectKey : public IGranulesManager {
	public:
		IProtectKey(void);
		virtual ~IProtectKey(void);

		virtual const bool check_license(void) const = 0;
		virtual const bool is_key_nfr(void) const = 0;
		virtual const bool is_key_base(void) const = 0;
};
