
#include "stdafx.h"

#include "CheckMethodTest.h"
#include "MockRealKeyHaspSL.h"
#include "ProtectKeyHaspSL.h"
#include "CheckMethodMemory.h"

#pragma region Constructor Destructor
CheckMethodTest::CheckMethodTest(void) {
	const size_t licenses_amount = 2;
	const offset_t ro_memory_offset = 3;
	const value_t ro_memory_value = value_t{ 0x10, 0x00, 0x4a, 0x83 };

	check_method_login_t check_method_login;
	check_method_memory_t check_method_memory = std::make_shared<const CheckMethodMemory>(ro_memory_offset, ro_memory_value, check_method_login, KeyMemoryType::ReadOnly);

	check_methods_memory_t check_methods_memory;
	check_methods_memory.push_back(check_method_memory);

	auto key = std::make_shared<const MockRealKeyHaspSL>(feature, check_methods_memory);
	key->set_licenses_amount(licenses_amount);
	_protect_key_hasp_sl = std::make_shared<const ProtectKeyHaspSL>(key);
}
CheckMethodTest::~CheckMethodTest(void) {
}
#pragma endregion Constructor Destructor
