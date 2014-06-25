
#ifndef __PROTECTKEYROCKEYLOCAL_H__
#define __PROTECTKEYROCKEYLOCAL_H__

#include "ProtectKeyRockey.h"

class ProtectKeyRockeyLocal : public ProtectKeyRockey {
	public:
		ProtectKeyRockeyLocal(const real_key_rockey_t key);
		~ProtectKeyRockeyLocal(void);
};

#endif // __PROTECTKEYROCKEYLOCAL_H__
