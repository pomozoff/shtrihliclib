
#pragma once

#include "Platform.h"

class PlatformWindows : public Platform
{
	public:
		PlatformWindows(void);
		~PlatformWindows(void);

		virtual const std::string computer_name(void) const override;
		virtual const std::string user_name(void) const override;
		/* Accessors */
	protected:
};
