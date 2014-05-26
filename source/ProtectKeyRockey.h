
#pragma once

#include "rockey/ryvc32.h"
#include "ProtectKey.h"

class LicenseBlock;
class LicenseBlockManager;

class ProtectKeyRockey : public ProtectKey {
	public:
		ProtectKeyRockey(const real_key_rockey_t key, const size_t session_id_hash, const KeyType keytype);
		~ProtectKeyRockey(void);

		static const size_t key_type_rockey4_local = 3;
		static const size_t key_type_rockey4_net = 6;

		static const size_t memory_size_rockey4_local = 24;
		static const size_t memory_size_rockey4_net = 120;

		/* ProtectKey Interface */
		virtual const value_t read_memory(const check_method_memory_t check_method) const override final;

		/* IKeyChecker Interface */
		virtual const bool is_able_to_login(const check_method_login_t check_method) const override final;
		virtual const bool is_same_memory(const check_method_memory_t check_method) const override final;
		virtual const bool logout_key(const check_method_login_t check_method) const override final;
	protected:
		/* KeyChecker Interface */
		virtual const key_handle_t get_handle(const check_method_login_t check_method) const override final;
	private:
		const real_key_rockey_t _real_key;
		mutable check_method_login_t _last_loggedin_method;

		const std::string key_id(const rockey_handle_t handle) const;

		const rockey_status_t read_memory(const check_method_login_t check_method, const rockey_size_t offset, const rockey_size_t length, value_t& buffer) const;
		const rockey_status_t write_memory(const check_method_login_t check_method, const rockey_size_t offset, const rockey_size_t length, const value_t& buffer) const;

		const bool login(const check_method_login_t check_method, rockey_handle_t& handle) const;
		const size_t licenses_amount(const check_method_login_t check_method) const;

		void process_result(const rockey_status_t status) const;
};
