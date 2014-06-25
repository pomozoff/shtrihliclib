
#ifndef __REALKEYROCKEYLOCAL_H__
#define __REALKEYROCKEYLOCAL_H__

#include "RealKeyRockey.h"

class RealKeyRockeyLocal : public RealKeyRockey {
	public:
		RealKeyRockeyLocal(void);
		virtual ~RealKeyRockeyLocal(void);
	protected:
		virtual const size_t max_memory_size(void) const;

		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
	private:
		static const size_t _key_type = 3;
		static const size_t _memory_size = 24;
};

#endif // __REALKEYROCKEYLOCAL_H__
