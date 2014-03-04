
#pragma once

#include "Platform.h"

class PlatformLinux : public Platform
{
	public:
		PlatformLinux(void);
		~PlatformLinux(void);

		/* Accessors */
		virtual const std::string computer_name(void) const override final;
		virtual const std::string user_name(void) const override final;
	protected:
};
