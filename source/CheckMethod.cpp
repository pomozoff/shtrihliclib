
#include "stdafx.h"
#include "CheckMethod.h"
#include "CheckMethodBase.h"
#include "CheckMethodLogin.h"
#include "CheckMethodMemory.h"

CheckMethod::CheckMethod(void) {
}
CheckMethod::~CheckMethod(void) {
}

CheckMethod* CheckMethod::create_check_method_base(void) {
	return new CheckMethodBase();
}
CheckMethod* CheckMethod::create_check_method_login(const feature_t feature) {
	return CheckMethod::create_check_method_login(feature, false);
}
CheckMethod* CheckMethod::create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key) {
	return new CheckMethodLogin(feature, allow_to_login_on_previous_key);
}
CheckMethod* CheckMethod::create_check_method_memory(const offset_t offset, const std::vector<byte_t>& value, const CheckMethodLogin& logged_in_method) {
	return new CheckMethodMemory(offset, value, logged_in_method);
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
