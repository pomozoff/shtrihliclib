
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
		virtual const uint16_t call_rockey(uint16_t function, uint16_t* handle, uint32_t* lp1, uint32_t* lp2, uint16_t* p1, uint16_t* p2, uint16_t* p3, uint16_t* p4, uint8_t* buffer) const override;
	private:
		static const size_t _key_type = 3;
		static const size_t _memory_size = 24;
};

#endif // __REALKEYROCKEYLOCAL_H__
