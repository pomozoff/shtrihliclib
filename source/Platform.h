
#pragma once

#include "DataTypes.h"

class Platform {
	public:
		virtual ~Platform(void);

		static const platform_t platform(void);

		/* Accessors */
		virtual const std::string computer_name(void) const = 0;
		virtual const std::string user_name(void) const = 0;
	protected:
		Platform(void);

		std::string _computer_name;
		std::string _user_name;
};
