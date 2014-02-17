
#pragma once

#include "Platform.h"

class PlatformLinux : public Platform
{
	public:
		PlatformLinux(void);
		~PlatformLinux(void);

		virtual const std::string computer_name(void) const override;
		virtual const std::string user_name(void) const override;
	protected:
};
