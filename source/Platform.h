
#pragma once

#include "DataTypes.h"

class Platform {
	public:
		virtual ~Platform(void);

		static const platform_t platform(void);

		/* Accessors */
		const std::string computer_name(void) const;
		const std::string user_name(void) const;
	protected:
		Platform(const std::string computer_name, const std::string user_name);

		std::string _computer_name;
		std::string _user_name;
};
