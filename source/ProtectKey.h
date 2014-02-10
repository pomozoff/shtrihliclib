
#pragma once

#include "IProtectKey.h"
#include "KeyChecker.h"

class ProtectKey : public IProtectKey, KeyChecker {
	public:
		ProtectKey(void);
		~ProtectKey(void);
	protected:
		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const override;
		virtual const bool is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
		virtual const bool is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const override;
		virtual const bool logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
};
