
#pragma once

#include "hasp/hasp_api.h"

#include "ProtectKey.h"
#include "LicenseBlock.h"
#include "LicenseBlockManager.h"

class ProtectKeyHaspSL final : public ProtectKey {
	public:
		ProtectKeyHaspSL(const i_real_key_hasp_t key, const size_t session_id_hash);
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

		/* IProtectKey Interface */
		//virtual const bool decrypt(byte_t* buffer, const size_t length) const override final;
	protected:
		// Наследование из базового класса ProtectKey
		const KeyType _key_type = KeyType::HaspSL;
		const time_t _timeout_check = 10; // Проверять лицензию каждые 10 секунд

		/* KeyChecker Interface */
		virtual const key_handle_t get_handle(const check_method_login_t check_method) const override final;
	private:
		static const time_t license_timeout = 60; // Одна минута

		const i_real_key_hasp_t _real_key;
		mutable check_method_login_t _last_loggedin_method;

		const std::string key_id(const hasp_handle_t handle) const;

		const hasp_status_t read_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const;
		const hasp_status_t write_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const;

		const bool login(const check_method_login_t check_method, hasp_handle_t& handle) const;
		const size_t licenses_amount(const check_method_login_t check_method) const;
		const bool get_license(const check_method_login_t check_method) const;

		const license_block_manager_t make_license_block_manager(const check_method_login_t check_method) const;
		void free_licnese(void) const;

		void process_result(const hasp_status_t status) const;
};
