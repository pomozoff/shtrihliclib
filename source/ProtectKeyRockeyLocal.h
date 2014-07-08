
#ifndef __PROTECTKEYROCKEYLOCAL_H__
#define __PROTECTKEYROCKEYLOCAL_H__

#include "ProtectKeyRockey.h"

class ProtectKeyRockeyLocal : public ProtectKeyRockey {
	public:
		ProtectKeyRockeyLocal(const real_key_rockey_t key);
		~ProtectKeyRockeyLocal(void);

		/* IKeyChecker Interface */
		virtual const std::string get_key_type(void) const override final;
};

#endif // __PROTECTKEYROCKEYLOCAL_H__
