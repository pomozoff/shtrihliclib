
#ifndef __REALKEYHASP_H__
#define __REALKEYHASP_H__

#include "hasp/hasp_api.h"
#include "RealKey.h"

class RealKeyHasp : public RealKey<hasp_status_t> {
	public:
		RealKeyHasp(void);
		virtual ~RealKeyHasp(void);

		inline const hasp_fileid_t hasp_memory_type(const KeyMemoryType memory_type) const {
			return memory_type == KeyMemoryType::ReadOnly ? HASP_FILEID_RO : HASP_FILEID_RW;
		}

		virtual const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const = 0;
		virtual const hasp_status_t _hasp_read(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const;
		virtual const hasp_status_t _hasp_write(const hasp_handle_t handle, const hasp_fileid_t file_id, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const;
		virtual const hasp_status_t _hasp_logout(const hasp_handle_t handle) const;
		virtual const hasp_status_t _hasp_legacy_set_idletime(const hasp_handle_t handle, const hasp_u16_t idle_time) const;
		virtual const hasp_status_t _hasp_decrypt(const hasp_handle_t handle, byte_t* buffer, const hasp_size_t length) const;
};

#endif // __REALKEYHASP_H__
