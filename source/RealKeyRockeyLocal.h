
#ifndef __REALKEYROCKEYLOCAL_H__
#define __REALKEYROCKEYLOCAL_H__

#include "RealKeyRockey.h"

class RealKeyRockeyLocal : public RealKeyRockey {
	public:
		RealKeyRockeyLocal(void);
		virtual ~RealKeyRockeyLocal(void);
	protected:
		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
};

#endif // __REALKEYROCKEYLOCAL_H__
