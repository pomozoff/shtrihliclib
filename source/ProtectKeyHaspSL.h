
#ifndef __PROTECTKEYHASPSL_H__
#define __PROTECTKEYHASPSL_H__

#include "hasp/hasp_api.h"
#include "ProtectKey.h"

class LicenseBlock;
class LicenseBlockManager;

class ProtectKeyHaspSL final : public ProtectKey {
	private:
		static const check_number_t _max_check_number = 10;
	public:
		ProtectKeyHaspSL(const real_key_hasp_t key, const size_t session_id_hash);
		~ProtectKeyHaspSL(void);

		static const size_t read_only_memory_size = 64;
		static const size_t read_write_memory_size = 4032;
		static const offset_t offset_licenses_amount = 8;

		/* ProtectKey Interface */
		virtual const value_t read_memory(const check_method_memory_t check_method) const override final;

		/* IKeyChecker Interface */
		virtual const bool is_able_to_login(const check_method_login_t check_method) const override final;
		virtual const bool is_same_memory(const check_method_memory_t check_method) const override final;
		virtual const bool logout_key(const check_method_login_t check_method) const override final;
		virtual const std::string get_key_type(void) const override final;

		/* IProtectKey Interface */
		//virtual const bool decrypt(byte_t* buffer, const size_t length) const override final;
	protected:
		const size_t _session_id_hash;

		/* KeyChecker Interface */
		virtual const key_handle_t get_handle(const check_method_login_t check_method) const override final;
		virtual const check_number_t max_check_number(void) const override;
	private:
		const real_key_hasp_t _real_key;
		const size_t _key_polling_period_seconds = 17;

		const std::string key_id(const hasp_handle_t handle) const;

		const hasp_status_t read_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const;
		const hasp_status_t write_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const;

		const bool login(const check_method_login_t check_method, hasp_handle_t& handle) const;
		const size_t licenses_amount(const check_method_login_t check_method) const;
		const bool get_license(const check_method_login_t check_method) const;

		const license_block_manager_t make_license_block_manager(const check_method_login_t check_method, const time_t loggedin_period_seconds) const;
		void free_licnese(void) const;

		void process_result(const hasp_status_t status) const;
		const time_t get_random_timeout_seconds(void) const;
};

#endif // __PROTECTKEYHASPSL_H__
