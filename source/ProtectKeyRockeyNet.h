
#ifndef __PROTECTKEYROCKEYNET_H__
#define __PROTECTKEYROCKEYNET_H__

#include "ProtectKeyRockey.h"

class ProtectKeyRockeyNet : public ProtectKeyRockey {
public:
	ProtectKeyRockeyNet(const real_key_rockey_t key);
	~ProtectKeyRockeyNet(void);

	/* IKeyChecker Interface */
	virtual const std::string get_key_type(void) const override final;
};

#endif // __PROTECTKEYROCKEYNET_H__
