
#pragma once

#include "IRealKeyHasp.h"

class RealKeyHaspSL : public IRealKeyHasp {
	public:
		RealKeyHaspSL(void);
		virtual ~RealKeyHaspSL(void);

		/* IProtectKey IRealKeyHasp */
		virtual const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const override final;
		virtual const hasp_status_t _hasp_read(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, value_t& buffer) const override final;
		virtual const hasp_status_t _hasp_write(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, const value_t& buffer) const override final;
		virtual const hasp_status_t _hasp_logout(const hasp_handle_t handle) const  override final;
	protected:
};