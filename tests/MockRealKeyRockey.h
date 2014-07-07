
#ifndef __MOCKREALCKEYROCKEY_H__
#define __MOCKREALCKEYROCKEY_H__

#include "MockRealKey.h"
#include "RealKeyRockey.h"

class MockRealKeyRockey : public MockRealKey, public RealKeyRockey {
	public:
		MockRealKeyRockey(const rockey_feature_t feature_id, const check_methods_memory_t check_methods_memory);
		virtual ~MockRealKeyRockey(void);

		virtual const size_t max_memory_size(void) const = 0;
		void initialize_memory(const check_methods_memory_t& check_methods_memory) const;

		/* RealKeyRockey */
		virtual const rockey_status_t _rockey_login(const rockey_feature_t feature_id, std::string& key_number, rockey_handle_t& handle) const;
		virtual const rockey_status_t _rockey_read(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const;
		virtual const rockey_status_t _rockey_write(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const;
		virtual const rockey_status_t _rockey_logout(const rockey_handle_t handle) const;
	protected:
		const rockey_feature_t _feature_id;
		mutable value_t _buffer;
	private:
		const rockey_status_t check_memory(const rockey_handle_t handle, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer, value_t** local_buffer) const;
};

#endif // __MOCKREALCKEYROCKEY_H__
