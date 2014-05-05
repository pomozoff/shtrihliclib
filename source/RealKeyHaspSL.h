
#pragma once

#include "IRealKeyHasp.h"

class RealKeyHaspSL : public IRealKeyHasp {
	public:
		RealKeyHaspSL(void);
		virtual ~RealKeyHaspSL(void);

		/* IRealKeyHasp Interface */
		virtual const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const override;
		virtual const hasp_status_t _hasp_read(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const override;
		virtual const hasp_status_t _hasp_write(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const override;
		virtual const hasp_status_t _hasp_logout(const hasp_handle_t handle) const override;
		virtual const hasp_status_t _hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const override;
		virtual const hasp_status_t _hasp_decrypt(const hasp_handle_t handle, byte_t* buffer, const hasp_size_t length) const override;
};
