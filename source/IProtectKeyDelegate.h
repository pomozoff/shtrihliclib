
#pragma once

#include "stdafx.h"

class IProtectKeyDelegate {
	public:
		IProtectKeyDelegate(void);

		virtual void did_check_protect_key(const bool success) = 0;
	protected:
		virtual ~IProtectKeyDelegate(void);
};
