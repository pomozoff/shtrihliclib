
#include "StdAfx.h"
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
CheckMethod* CheckMethod::create_check_method_login(const unsigned long program_number) {
	return CheckMethod::create_check_method_login(program_number, false);
}
CheckMethod* CheckMethod::create_check_method_login(const unsigned long program_number, const bool allow_to_login_on_previous_key) {
	return new CheckMethodLogin(program_number, allow_to_login_on_previous_key);
}
CheckMethod* CheckMethod::create_check_method_memory(const unsigned long offset, const unsigned char* value, const CheckMethodLogin* logged_in_method) {
	return new CheckMethodMemory(offset, value, logged_in_method);
}

bool CheckMethod::process_check_result(const bool last_check_is_success) {
	return false;
}
