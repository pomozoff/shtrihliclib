
#ifndef __PROTECTKEY_H__
#define __PROTECTKEY_H__

#include <ctime>

#include "IProtectKey.h"
#include "KeyChecker.h"
#include "IProtectKeyDelegate.h"

class ProtectKey;
class Granule;

using protect_key_t = std::shared_ptr<const ProtectKey>;
using protect_key_weak_t = std::weak_ptr<const ProtectKey>;
using protect_keys_t = std::vector<const protect_key_t>;
using granules_t = std::map<const granule_t, bool>;
using iprotect_key_t = std::shared_ptr<const IProtectKey>;
using iprotect_key_weak_t = std::weak_ptr<const IProtectKey>;

enum class KeyType { Base, HaspSL, HaspHLLocal, HaspHLNet, RockeyLocal, RockeyNet, FileMapped };

class ProtectKey : public IProtectKey, public KeyChecker, public std::enable_shared_from_this<const ProtectKey> {
	public:
		~ProtectKey(void);
		
		static const std::wstring session_id(platform_t platform);
		static const size_t hash_from_session_id(const std::wstring session_id);
		static const protect_key_t create_key(const KeyType key_type, const platform_t platform);

		static const iprotect_key_weak_t find_key(const protect_keys_t& keys_list, IProtectKeyDelegate& key_delegate);
		static const bool copy_block_to_buffer(const value_t& source, value_t& destination, const size_t length, const offset_t source_offset, const offset_t destination_offset);

		const granule_t create_granule(const std::wstring id) const;
		void remove_granules(void) const;

		virtual const value_t read_memory(const check_method_memory_t check_method) const = 0;

		virtual const granule_t granule_with_name(const std::wstring& granule_name) const override final;
		virtual const bool is_granule_present(const granule_t& granule) const override final;

		/* IProtectKey Interface */
		virtual const bool check_license(void) const override final;
		virtual const bool is_key_nfr(void) const override final;
		virtual const bool is_key_base(void) const override final;
		virtual const size_t licenses_amount(void) const override final;

		virtual const time_t check_license_timeout(void) const override final;
		virtual void encrypt(const byte_t* input_buffer, const size_t input_length, byte_t** iv_enc, size_t& iv_length, byte_t** encrypted_buffer, size_t& encrypted_length) const override final;
		virtual void decrypt(const byte_t* encrypted_buffer, const size_t encrypted_length, byte_t* iv_dec, byte_t** decrypted_buffer) const override final;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const check_method_base_t check_method) const override;
		virtual const bool is_able_to_login(const check_method_login_t check_method) const override;
		virtual const bool is_same_memory(const check_method_memory_t check_method) const override;
		virtual const bool logout_key(const check_method_login_t check_method) const override;
		virtual const std::string get_key_number(void) const override final;

		/* Accessors */
		const bool logout_after_check(void) const;
		void set_logout_after_check(const bool logout_after_check) const;
		const time_t nfr_end_date(void) const;
		void set_nfr_end_date(const time_t nfr_end_date) const;
		void set_current_check_number(const check_number_t number) const;
	protected:
		const KeyType _keytype;
		time_t _license_timeout = 60; // ���� ������
		
		mutable std::string _key_number;
		mutable std::wstring _error_string;
		mutable size_t _error_code;
		mutable features_t _features;
		mutable check_number_t _current_check_number;
		mutable bool _first_key_check = true;
		mutable size_t _licenses_amount = 0;

		ProtectKey(const KeyType keytype, const check_number_t check_number);

		static const protect_key_t create_key(const KeyType key_type, const std::wstring session_id);

		void check_granules(void) const;
		void try_to_logout(void) const;
		virtual void init_key(void) const;

		/* KeyChecker Interface */
		virtual const bool check(void) const override final;
	
		/* IProtectKey Interface */
		virtual const time_t get_nfr_end_date(void) const override final;
	private:
		ProtectKey& operator=(const ProtectKey &tmp);

		const time_t _wait_period_milsec = 500;

		mutable IProtectKeyDelegate* _key_delegate;
		mutable granules_t _granules;
		mutable bool _logout_after_check = false;
		bool _is_key_base = false;

		mutable time_t _nfr_end_date = std::time(NULL);
		mutable bool _is_key_nfr = false;

		virtual const size_t read_licenses_amount(const check_method_login_t check_method) const = 0;

		const bool check_license_with_methods(void) const;
		const bool recheck_key(void) const;

		const bool process_check_result(const bool last_check_is_success) const;

		template <class C, typename R, typename T>
		using member_function_t = R(C::*)(T value) const;
};

#endif // __PROTECTKEY_H__
