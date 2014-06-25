
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "DataTypes.h"

class Platform {
	public:
		virtual ~Platform(void);

		static const platform_t platform(void);
		const std::wstring session_id(void) const;
	protected:
		Platform(const std::wstring computer_name, const std::wstring user_name);

		std::wstring _computer_name;
		std::wstring _user_name;
};

#endif // __PLATFORM_H__
