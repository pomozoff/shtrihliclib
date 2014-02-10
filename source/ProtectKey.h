
#pragma once

#include "IProtectKey.h"
#include "IProtectKeyDelegate.h"
#include "KeyChecker.h"
#include "Granule.h"

class ProtectKey;

using keys_list_t = std::vector<const std::shared_ptr<const ProtectKey>>;

enum class KeyType { Base, HaspSL, HaspHLLocal, HaspHLNet, RockeyLocal, RockeyNet, FileMapped };

class ProtectKey : public IProtectKey, public KeyChecker, public std::enable_shared_from_this<const ProtectKey> {
	public:
		ProtectKey(void);
		~ProtectKey(void);

		static const std::unique_ptr<const ProtectKey> create_key(const KeyType key_type);
		static const std::shared_ptr<const IProtectKey> find_key(const keys_list_t keys_list, const std::shared_ptr<IProtectKeyDelegate> key_delegate);
	protected:
		mutable KeyType m_key_type;

		virtual const bool check(void) const override;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const override;
		virtual const bool is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
		virtual const bool is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const override;
		virtual const bool logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
	private:
		std::vector<const Granule> m_granules;
		bool m_is_key_base = false;
		mutable bool m_is_key_nfr = false;
		mutable std::shared_ptr<const IProtectKeyDelegate> m_key_delegate;

};
