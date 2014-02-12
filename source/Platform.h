
#pragma once

#include "DataTypes.h"

class Platform {
	public:
		virtual ~Platform();

		static const platform_t platform(void);

		virtual const std::string computer_name(void) const = 0;
		virtual const std::string user_name(void) const = 0;
	protected:
		Platform();
};
