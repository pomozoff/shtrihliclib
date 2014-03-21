
#pragma once

#include "Platform.h"

class PlatformLinux final : public Platform
{
	public:
		PlatformLinux(void);
		~PlatformLinux(void);
	protected:
	private:
		const std::string get_computer_name(void) const;
		const std::string get_user_name(void) const;
};
