
#include "stdafx.h"
#include "KeyChecker.h"

KeyChecker::KeyChecker(void){
}
KeyChecker::~KeyChecker(void){
}

const bool KeyChecker::is_able_to_login(const CheckMethodLogin& checkMethod) const {
	return false;
}
const bool KeyChecker::is_same_memory(const CheckMethodMemory& checkMethod) const {
	return false;
}
const bool KeyChecker::logout_key(const CheckMethodLogin& checkMethod) const {
	return false;
}
const bool KeyChecker::is_key_available(const CheckMethodBase& checkMethod) const {
	return false;
}
