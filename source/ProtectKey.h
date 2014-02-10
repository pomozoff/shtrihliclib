
#pragma once

#include "IProtectKey.h"
#include "KeyChecker.h"
#include "Granule.h"

enum class KeyType { Base, HaspSL, HaspHLLocal, HaspHLNet, RockeyLocal, RockeyNet, FileMapped };

class ProtectKey : public IProtectKey, public KeyChecker, public std::enable_shared_from_this<const ProtectKey> {
	public:
		ProtectKey(void);
		~ProtectKey(void);

		static const std::unique_ptr<const ProtectKey> create_key(const KeyType key_type);
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
};
