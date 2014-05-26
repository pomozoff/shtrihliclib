
#pragma once

#include "RealKeyRockey.h"

using check_methods_memory_t = std::vector<const check_method_memory_t>;

class MockRealKeyRockeyLocal : public RealKeyRockey {
	public:
		MockRealKeyRockeyLocal(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory);
		virtual ~MockRealKeyRockeyLocal();

		/* RealKeyRockey */
		virtual const rockey_status_t _rockey_login(const rockey_feature_t feature_id, const rockey_passwords_t passwords, rockey_handle_t& handle) const;
		virtual const rockey_status_t _rockey_read(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const;
		virtual const rockey_status_t _rockey_write(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const;
		virtual const rockey_status_t _rockey_logout(const rockey_handle_t handle) const;
	protected:
		const rockey_feature_t _feature_id;
		mutable value_t _buffer;
	private:
		void initialize_memory(const check_methods_memory_t& check_methods_memory) const;
		const rockey_status_t check_memory(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer, value_t** local_buffer) const;
};
