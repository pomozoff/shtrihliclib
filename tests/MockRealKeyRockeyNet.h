
#ifndef __MOCKREALCKEYROCKEYNET_H__
#define __MOCKREALCKEYROCKEYNET_H__

#include "MockRealKeyRockey.h"

class MockRealKeyRockeyNet : public MockRealKeyRockey {
	public:
		MockRealKeyRockeyNet(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory);
		virtual ~MockRealKeyRockeyNet();
	protected:
		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
};

#endif // __MOCKREALCKEYROCKEYNET_H__
