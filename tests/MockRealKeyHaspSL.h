
#pragma once

#include "RealKeyHaspSL.h"

using check_methods_memory_t = std::vector<const check_method_memory_t>;

class MockRealKeyHaspSL : public RealKeyHaspSL {
	public:
		MockRealKeyHaspSL(const hasp_feature_t feature_id, const check_methods_memory_t check_methods_memory);
		virtual ~MockRealKeyHaspSL();

		void set_licenses_amount(const uint16_t amount) const;

		/* RealKeyHasp */
		virtual const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const override;
		virtual const hasp_status_t _hasp_read(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const override;
		virtual const hasp_status_t _hasp_write(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const override;
		virtual const hasp_status_t _hasp_logout(const hasp_handle_t handle) const  override;
		virtual const hasp_status_t _hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const override;
	protected:
		const hasp_feature_t _feature_id;
		mutable value_t _ro_buffer;
		mutable value_t _rw_buffer;
	private:
		void initialize_memory(const check_methods_memory_t& check_methods_memory) const;
		const hasp_status_t check_memory(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const int length, const value_t& buffer, value_t** local_buffer) const;
		value_t* const get_buffer_by_memory_type(const hasp_fileid_t file_id) const;
};
