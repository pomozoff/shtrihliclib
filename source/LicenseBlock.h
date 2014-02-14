
#pragma once

#include "DataTypes.h"

class LicenseBlock final {
	private:
		static const size_t sizeof_hash = sizeof(size_t);
		static const size_t sizeof_data = sizeof_hash + sizeof(time_t);
	public:
		LicenseBlock(const value_t block, const offset_t offset, const time_t timeout);
		~LicenseBlock(void);

		static const size_t sizeof_block = sizeof_data + sizeof_hash;
		static const value_t create_block_as_buffer_from_string(const std::string session_id, const time_t time_logged_in);
	protected:
	private:
		const value_t _block;
		const offset_t _offset_in_manager;
		const time_t _timeout;

		template <typename T>
		static const bool place_data_to_buffer_at_offset(const T data, value_t& buffer, const offset_t offset);
		static const value_t create_block_as_buffer_from_hash(const size_t hash, const time_t time_logged_in);
		static const size_t hash_value(value_t buffer);
};
