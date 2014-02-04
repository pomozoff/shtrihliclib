
#pragma once

#include "IKeyChecker.h"
#include "ICheckMethodsManager.h"
#include "ICheckMethodsViewer.h"

class KeyChecker : public IKeyChecker, ICheckMethodsManager, ICheckMethodsViewer {
	public:
		KeyChecker(void);
		~KeyChecker(void);
	private:
		virtual bool isAbleToLogin(CheckMethodLogin* checkMethod) override;
};
