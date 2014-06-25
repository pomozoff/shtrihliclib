
#ifndef __REALKEYROCKEYNET_H__
#define __REALKEYROCKEYNET_H__

#include "RealKeyRockey.h"

class RealKeyRockeyNet : public RealKeyRockey {
	public:
		RealKeyRockeyNet(void);
		virtual ~RealKeyRockeyNet(void);

		RealKeyRockeyNet& RealKeyRockeyNet::operator=(const RealKeyRockeyNet& other);
		RealKeyRockeyNet& RealKeyRockeyNet::operator=(RealKeyRockeyNet&& other);
	protected:
		virtual const size_t max_memory_size(void) const;

		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
	private:
		static const size_t _key_type = 6;
		static const size_t _memory_size = 120;

		const bool _is_terminal_mode;
		const bool is_terminal_mode_detected(void) const;
};

#endif // __REALKEYROCKEYNET_H__
