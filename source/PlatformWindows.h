
#pragma once

#include "Platform.h"

class PlatformWindows : public Platform
{
	public:
		PlatformWindows();
		~PlatformWindows();

		virtual const std::string computer_name(void) const override;
		virtual const std::string user_name(void) const override;
	protected:
};
