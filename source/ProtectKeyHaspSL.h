
#pragma once

#include "hasp/hasp_api.h"

#include "ProtectKey.h"
class ProtectKeyHaspSL final : public ProtectKey {
	public:
		ProtectKeyHaspSL(void);
		~ProtectKeyHaspSL(void);

		static const size_t read_write_memory_size = 4032;

		/* ProtectKey Interface */
		virtual const value_t read_memory(const check_method_memory_t check_method) const override final;

		/* IKeyChecker Interface */
		virtual const bool is_able_to_login(const check_method_login_t check_method) const override final;
		virtual const bool is_same_memory(const check_method_memory_t check_method) const override final;
		virtual const bool logout_key(const check_method_login_t check_method) const override final;
	protected:
		// Наследование из базового класса ProtectKey
		const KeyType _key_type = KeyType::HaspSL;
		const time_t _timeout_check = 10; // Проверять лицензию каждые 10 секунд

		/* KeyChecker Interface */
		virtual const handle_t get_handle(const check_method_login_t check_method) const override final;
		virtual void remove_handle(const check_method_login_t check_method) const override final;
	private:
		static const size_t read_only_memory_size = 64;
		static const time_t license_timeout = 60; // Одна минута

		check_method_login_t _last_loggedin_method;

		mutable hasp_status_t _last_status;

		const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const hasp_vendor_code_t vendor_code, hasp_handle_t handle) const;
		const hasp_status_t _hasp_read(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, value_t& buffer) const;
		const hasp_status_t _hasp_write(const hasp_handle_t handle, const size_t file_id, const hasp_size_t offset, const int length, const value_t& buffer) const;
		const hasp_status_t _hasp_logout(const hasp_handle_t handle) const;

		const std::string key_id(const hasp_handle_t handle) const;

		const hasp_status_t read_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, value_t& buffer) const;
		const hasp_status_t write_rw_memory(const check_method_login_t check_method, const hasp_size_t offset, const hasp_size_t length, const value_t& buffer) const;

		const bool login(const check_method_login_t check_method) const;
		const size_t licenses_amount(const check_method_login_t check_method) const;
		const bool get_license(const check_method_login_t check_method) const;

		void free_licnese(void) const;
};
