
#pragma once

#include "rockey/ryvc32.h"
#include "RealKey.h"

class RealKeyRockey : public RealKey<rockey_status_t> {
	public:
		RealKeyRockey(void);
		virtual ~RealKeyRockey(void);

		virtual const rockey_status_t _rockey_login(const rockey_feature_t feature_id, const rockey_passwords_t passwords, rockey_handle_t& handle) const;
		virtual const rockey_status_t _rockey_read(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const;
		virtual const rockey_status_t _rockey_write(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const;
		virtual const rockey_status_t _rockey_logout(const rockey_handle_t handle) const;
};
