﻿
#pragma once

#include "CheckMethod.h"

class CheckMethodMemory final : public CheckMethod, public std::enable_shared_from_this<CheckMethodMemory> {
	public:
		CheckMethodMemory(const feature_t offset, const value_t& value, const check_method_t logged_in_method);
		~CheckMethodMemory(void);

		virtual const bool check(const ikey_checker_t key_checker) const override final;
	protected:
	private:
		// Наследование из базового класса CheckMethod
		const CheckMethodType _check_method = CheckMethodType::Memory;
	private:
		const offset_t _offset;
		const value_t _value;
		const check_method_t _logged_in_method;
};
