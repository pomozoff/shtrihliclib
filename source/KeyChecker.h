
#pragma once

#include "IKeyChecker.h"
#include "ICheckMethodsManager.h"
#include "ICheckMethodsViewer.h"

class KeyChecker : public IKeyChecker, ICheckMethodsManager, ICheckMethodsViewer {
	public:
		KeyChecker(void);
		~KeyChecker(void);
	private:
		virtual bool const is_able_to_login(const CheckMethodLogin& checkMethod) const override;
};
