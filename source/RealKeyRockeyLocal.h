
#pragma once

#include "RealKeyRockey.h"

class RealKeyRockeyLocal : public RealKeyRockey {
	public:
		RealKeyRockeyLocal(void);
		virtual ~RealKeyRockeyLocal(void);
	protected:
		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
};
