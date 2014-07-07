
#include "stdafx.h"

#include "CheckMethod.h"

#pragma region Constructor Destructor
CheckMethod::CheckMethod(const CheckMethodType check_method) :
_check_method(check_method)
{
}
CheckMethod::~CheckMethod(void) {
}
#pragma endregion

const CheckMethodType CheckMethod::check_method_type(void) const {
	return _check_method;
}

#pragma region Accessors
const bool CheckMethod::logout_after_check(void) const {
	return _logout_after_check;
}
const bool CheckMethod::is_check_method_for_nfr(void) const {
	return _is_check_method_for_nfr;
}
const bool CheckMethod::is_check_method_for_license(void) const {
	return _is_check_method_for_license;
}
void CheckMethod::set_logout_after_check(const bool logout_after_check) const {
	_logout_after_check = logout_after_check;
}
void CheckMethod::set_check_method_for_nfr(const bool check_method_for_nfr) const {
	_is_check_method_for_nfr = check_method_for_nfr;
}
void CheckMethod::set_check_method_for_license(const bool check_method_for_license) const {
	_is_check_method_for_license = check_method_for_license;
}
#pragma endregion
