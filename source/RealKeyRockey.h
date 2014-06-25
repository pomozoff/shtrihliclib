
#ifndef __REALKEYROCKEY_H__
#define __REALKEYROCKEY_H__

#include "rockey/ryvc32.h"
#include "RealKey.h"

using rockey_key_hid_t = uint32_t;
using rockey_keys_t = std::vector<const rockey_key_hid_t>;

class RealKeyRockey : public RealKey<rockey_status_t> {
	public:
		RealKeyRockey(void);
		virtual ~RealKeyRockey(void);

		virtual const size_t max_memory_size(void) const = 0;

		virtual const rockey_status_t _rockey_login(const rockey_feature_t feature_id, std::string& key_number, rockey_handle_t& handle) const;
		virtual const rockey_status_t _rockey_read(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const;
		virtual const rockey_status_t _rockey_write(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const;
		virtual const rockey_status_t _rockey_logout(const rockey_handle_t handle) const;
	protected:
		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const = 0;
	private:
		const rockey_status_t find_keys(rockey_keys_t& keys) const;

		mutable rockey_long_t _key_type = 0;
};

#endif // __REALKEYROCKEY_H__
