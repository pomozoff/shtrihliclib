
#ifndef __MOCKREALCKEYROCKEYLOCAL_H__
#define __MOCKREALCKEYROCKEYLOCAL_H__

#include "MockRealKeyRockey.h"

class MockRealKeyRockeyLocal : public MockRealKeyRockey {
	public:
		MockRealKeyRockeyLocal(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory);
		virtual ~MockRealKeyRockeyLocal();
	protected:
		virtual const size_t max_memory_size(void) const;
		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
	private:
		static const size_t _key_type = 3;
		static const size_t _memory_size = 24;
};

#endif // __MOCKREALCKEYROCKEYLOCAL_H__
