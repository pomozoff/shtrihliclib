
#include "StdAfx.h"
#include "CheckMethodLogin.h"
#include "IKeyChecker.h"

CheckMethodLogin::CheckMethodLogin(void) {
}
CheckMethodLogin::CheckMethodLogin(const unsigned long feature) {
	m_feature = feature;
}
CheckMethodLogin::~CheckMethodLogin(void) {
}

bool CheckMethodLogin::check(const IKeyChecker* key_checker) {
	return false;
};

check_method_t CheckMethodLogin::check_method_type(void) {
	return CHECK_METHOD_LOGIN;
}
