
#pragma once

#include "hasp/hasp_api.h"

#include "DataTypes.h"

class IRealKeyHasp {
	public:
		virtual ~IRealKeyHasp(void);

		virtual const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const = 0;
		virtual const hasp_status_t _hasp_read(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, value_t& buffer) const = 0;
		virtual const hasp_status_t _hasp_write(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, const value_t& buffer) const = 0;
		virtual const hasp_status_t _hasp_logout(const hasp_handle_t handle) const = 0;
		virtual const hasp_status_t _hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const = 0;

		/* Accessors */
		const hasp_status_t last_status(void) const;
	protected:
		IRealKeyHasp(void);

		mutable hasp_status_t _last_status;
};
