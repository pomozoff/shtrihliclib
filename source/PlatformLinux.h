
#ifndef __PLATFORMLINUX_H__
#define __PLATFORMLINUX_H__

#include "Platform.h"

class PlatformLinux final : public Platform
{
	public:
		PlatformLinux(void);
		~PlatformLinux(void);
	protected:
	private:
		const std::wstring get_computer_name(void) const;
		const std::wstring get_user_name(void) const;
};

#endif // __PLATFORMLINUX_H__
