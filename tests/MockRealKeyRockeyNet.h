
#ifndef __MOCKREALCKEYROCKEYNET_H__
#define __MOCKREALCKEYROCKEYNET_H__

#include "MockRealKeyRockey.h"

class MockRealKeyRockeyNet : public MockRealKeyRockey {
	public:
		MockRealKeyRockeyNet(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory, const bool is_key_nfr);
		virtual ~MockRealKeyRockeyNet(void);

		void set_licenses_amount(const size_t amount) const;
	protected:
		virtual const size_t max_memory_size(void) const override;
		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
		virtual const uint16_t call_rockey(uint16_t function, uint16_t* handle, uint32_t* lp1, uint32_t* lp2, uint16_t* p1, uint16_t* p2, uint16_t* p3, uint16_t* p4, uint8_t* buffer) const override;
	private:
		static const size_t _key_type = 6;
		static const size_t _memory_size = 120;
};

#endif // __MOCKREALCKEYROCKEYNET_H__
