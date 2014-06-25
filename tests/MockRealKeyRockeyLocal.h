
#ifndef __MOCKREALCKEYROCKEYLOCAL_H__
#define __MOCKREALCKEYROCKEYLOCAL_H__

#include "MockRealKeyRockey.h"

class MockRealKeyRockeyLocal : public MockRealKeyRockey {
	public:
		MockRealKeyRockeyLocal(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory);
		virtual ~MockRealKeyRockeyLocal();
	protected:
		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
};

#endif // __MOCKREALCKEYROCKEYLOCAL_H__
