
#include "StdAfx.h"
#include "CheckMethodLogin.h"
#include "IKeyChecker.h"

CheckMethodLogin::CheckMethodLogin(void) {
}
CheckMethodLogin::~CheckMethodLogin(void) {
}

bool CheckMethodLogin::check(IKeyChecker key_checker) {
	return false;
};
