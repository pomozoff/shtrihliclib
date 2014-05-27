
#pragma once

#include "RealKeyRockey.h"

class RealKeyRockeyNet : public RealKeyRockey {
	public:
		RealKeyRockeyNet(void);
		virtual ~RealKeyRockeyNet(void);
	protected:
		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
	private:
		const bool _is_terminal_mode;
		const bool is_terminal_mode_detected(void) const;
};
