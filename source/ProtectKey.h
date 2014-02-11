
#pragma once

#include "IProtectKey.h"
#include "IProtectKeyDelegate.h"
#include "KeyChecker.h"

class ProtectKey;
class Granule;

using keys_t = std::vector<const std::shared_ptr<const ProtectKey>>;
using granules_t = std::vector<const std::shared_ptr<const Granule>>;
using key_delegate_t = std::shared_ptr<const IProtectKeyDelegate>;

enum class KeyType { Base, HaspSL, HaspHLLocal, HaspHLNet, RockeyLocal, RockeyNet, FileMapped };

class ProtectKey : public IProtectKey, public KeyChecker, public std::enable_shared_from_this<const ProtectKey> {
	public:
		~ProtectKey(void);
		ProtectKey(void);

		static const std::unique_ptr<const ProtectKey> create_key(const KeyType key_type);
		static const std::shared_ptr<const IProtectKey> find_key(const keys_t keys_list, const std::shared_ptr<IProtectKeyDelegate> key_delegate);

		/* IProtectKey Interface */
		virtual const bool check_license(void) const override;
		virtual const bool is_key_nfr(void) const override;

		/* Properties */
		const bool logout_after_check(void) const;
		void set_logout_after_check(bool logout_after_check);
		const bool is_key_base(void) const;
	protected:
		KeyType _key_type;

		void check_granules(void) const;
		void try_to_logout(void) const;

		/* KeyChecker Interface */
		virtual const bool check(void) const override;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const override;
		virtual const bool is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
		virtual const bool is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const override;
		virtual const bool logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
	private:
		granules_t _granules;
		bool _logout_after_check = false;
		bool _is_key_base = false;
		mutable bool _is_key_nfr = false;
		mutable key_delegate_t _key_delegate;

		const bool check_license_with_methods(void) const;
		const bool recheck_key(void) const;
};
