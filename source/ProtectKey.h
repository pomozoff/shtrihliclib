
#pragma once

#include <chrono>

#include "IProtectKey.h"
#include "IProtectKeyDelegate.h"
#include "KeyChecker.h"

class ProtectKey;
class Granule;

using protect_key_t = std::shared_ptr<const ProtectKey>;
using protect_keys_t = std::vector<const protect_key_t>;
using granule_t = std::shared_ptr<const Granule>;
using granules_t = std::vector<const granule_t>;
using iprotect_key_delegate_t = std::shared_ptr<const IProtectKeyDelegate>;
using iprotect_key_t = std::shared_ptr<const IProtectKey>;

enum class KeyType { Base, HaspSL, HaspHLLocal, HaspHLNet, RockeyLocal, RockeyNet, FileMapped };

class ProtectKey : public IProtectKey, public KeyChecker, public std::enable_shared_from_this<const ProtectKey> {
	public:
		~ProtectKey(void);

		static const std::string session_id(void);
		static const size_t session_id_hash(void);

		static const protect_key_t create_key(const KeyType key_type);
		static const iprotect_key_t find_key(const protect_keys_t keys_list, const iprotect_key_delegate_t key_delegate);
		static const bool copy_block_to_buffer(const value_t& source, value_t& destination, const size_t length, const offset_t source_offset, const offset_t destination_offset);

		virtual const value_t read_memory(const check_method_memory_t checkMethod) const = 0;

		/* IProtectKey Interface */
		virtual const bool check_license(void) const override;
		virtual const bool is_key_nfr(void) const override;
		virtual const bool is_key_base(void) const override;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const check_method_base_t checkMethod) const override;
		virtual const bool is_able_to_login(const check_method_login_t checkMethod) const override;
		virtual const bool is_same_memory(const check_method_memory_t checkMethod) const override;
		virtual const bool logout_key(const check_method_login_t checkMethod) const override;

		/* Properties */
		const bool logout_after_check(void) const;
		void set_logout_after_check(const bool logout_after_check);
		const time_t nfr_end_date(void) const;
		void set_nfr_end_date(const time_t nfr_end_date) const;
	protected:
		KeyType _key_type;

		ProtectKey(void);

		void check_granules(void) const;
		void try_to_logout(void) const;

		/* KeyChecker Interface */
		virtual const bool check(void) const override;
	private:
		granules_t _granules;
		bool _logout_after_check = false;
		bool _is_key_base = false;

		mutable time_t _nfr_end_date = time(NULL);
		mutable bool _is_key_nfr = false;
		mutable iprotect_key_delegate_t _key_delegate = nullptr;

		const bool check_license_with_methods(void) const;
		const bool recheck_key(void) const;
};
