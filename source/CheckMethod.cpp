
#include "stdafx.h"

#include "CheckMethod.h"

CheckMethod::CheckMethod(void) {
}
CheckMethod::~CheckMethod(void) {
}

const CheckMethodType CheckMethod::check_method_type(void) const {
	return _check_method;
}
void CheckMethod::set_max_check_number(check_number_t check_number) const {
	_max_check_number = check_number;
}
const bool CheckMethod::is_check_method_for_NFR(void) const {
	return _is_check_method_for_NFR;
}
const bool CheckMethod::logout_after_check(void) const {
	return _logout_after_check;
}
const bool CheckMethod::is_check_method_for_license(void) const {
	return _is_check_method_for_license;
}
const bool CheckMethod::process_check_result(const bool last_check_is_success) const {
	if (last_check_is_success) {
		_current_check_number = 0;
		return true;
	}

	bool give_a_try_one_more_time = _current_check_number <= _max_check_number;
	if (give_a_try_one_more_time) {
		_current_check_number++;
	}

	return give_a_try_one_more_time;
}
