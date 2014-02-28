
#pragma once

#include "Platform.h"

class PlatformWindows : public Platform
{
	public:
		PlatformWindows(void);
		~PlatformWindows(void);

		/* Accessors */
		virtual const std::string computer_name(void) const override final;
		virtual const std::string user_name(void) const override final;
	protected:
};
