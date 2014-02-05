
#pragma once

#include "IKeyChecker.h"
#include "ICheckMethodsManager.h"
#include "ICheckMethodsViewer.h"

class KeyChecker : public IKeyChecker, ICheckMethodsManager, ICheckMethodsViewer {
	public:
		KeyChecker(void);
		~KeyChecker(void);
	private:
		virtual const bool is_able_to_login(const CheckMethodLogin& checkMethod) const override;
		virtual const bool is_same_memory(const CheckMethodMemory& checkMethod) const override;
		virtual const bool logout_key(const CheckMethodLogin& checkMethod) const override;
		virtual const bool is_key_available(const CheckMethodBase& checkMethod) const override;
};
