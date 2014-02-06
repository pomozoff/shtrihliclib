
#include "stdafx.h"

#include "CheckMethod.h"

CheckMethod::CheckMethod(void) {
}
CheckMethod::~CheckMethod(void) {
}

const CheckMethodType CheckMethod::check_method_type(void) const {
	return m_check_method;
}
const bool CheckMethod::process_check_result(const bool last_check_is_success) const {
	if (last_check_is_success) {
		m_current_check_number = 0;
		return true;
	}

	bool give_a_try_one_more_time = m_current_check_number <= m_max_check_number;
	if (give_a_try_one_more_time) {
		m_current_check_number++;
	}

	return give_a_try_one_more_time;
}
