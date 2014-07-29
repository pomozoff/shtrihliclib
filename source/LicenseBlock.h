
#ifndef __LICENSEBLOCK_H__
#define __LICENSEBLOCK_H__

class LicenseBlock final {
	private:
		static const size_t sizeof_hash = sizeof(size_t);
		static const size_t sizeof_data = sizeof_hash + sizeof(time_t);
	public:
		LicenseBlock(const value_t block, const offset_t offset, const time_t loggedin_period_seconds, const size_t session_id_hash);
		~LicenseBlock(void);

		static const size_t sizeof_block = sizeof_data + sizeof_hash;
		static const value_t block_from_string(const std::wstring session_id, const time_t loggedin_until_value);

		const size_t position_in_manager(void) const;
		const bool is_expired(void) const;
		const bool is_it_my_block(void) const;

		void update_block(const time_t time) const;
		void make_expired(void) const;

		/* Accessors */
		const offset_t offset_in_manager(void) const;
		const value_t& block(void) const;
		const time_t loggedin_period_seconds(void) const;
		const time_t loggedin_until(void) const;
	protected:
	private:
		LicenseBlock& operator=(const LicenseBlock &tmp);

		mutable value_t _block;
		const offset_t _offset_in_manager;
		const time_t _loggedin_period_seconds;
		const size_t _current_session_id_hash;

		template <typename T>
		static const bool place_data_to_buffer_at_offset(value_t& buffer, const offset_t offset, const T data);
		template <typename T>
		static const bool get_data_from_buffer_at_offset(const value_t buffer, const offset_t offset, T& data);

		static const value_t block_from_hash(const size_t hash, const time_t loggedin_until_value);
		static const size_t hash_value(const value_t buffer, const offset_t offset, const size_t size);

		const bool is_valid(void) const;
};

#endif // __LICENSEBLOCK_H__
