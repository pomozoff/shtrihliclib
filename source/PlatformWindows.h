
#pragma once

#include "Platform.h"

class PlatformWindows final : public Platform
{
	public:
		PlatformWindows(void);
		~PlatformWindows(void);
	protected:
	private:
		const std::string get_computer_name(void) const;
		const std::string get_user_name(void) const;
};
