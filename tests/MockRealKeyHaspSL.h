
#pragma once

#include "RealKeyHaspSL.h"

class MockRealKeyHaspSL : public RealKeyHaspSL {
	public:
		MockRealKeyHaspSL(const hasp_feature_t feature_id);
		virtual ~MockRealKeyHaspSL();

		/* IProtectKey IRealKeyHasp */
		virtual const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const override;
		virtual const hasp_status_t _hasp_read(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, value_t& buffer) const override;
		virtual const hasp_status_t _hasp_write(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, const value_t& buffer) const override;
		virtual const hasp_status_t _hasp_logout(const hasp_handle_t handle) const  override;
		virtual const hasp_status_t _hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const override;
	protected:
		const hasp_feature_t _feature_id;
		mutable value_t _ro_buffer;
		mutable value_t _rw_buffer;

		const hasp_status_t check_memory(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, const value_t& buffer, value_t** local_buffer) const;
		void initialize_ro_memory(value_t& buffer) const;
		void initialize_rw_memory(value_t& buffer) const;
	private:
		const offset_t _ro_memory_offset = 3;
		const value_t _ro_memory_value = value_t{ 0x10, 0x00, 0x4a, 0x83 };
};
