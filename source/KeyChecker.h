﻿
#pragma once

#include <memory>
#include <vector>
#include <map>

#include "IKeyChecker.h"
#include "ICheckMethodsManager.h"
#include "ICheckMethodsViewer.h"
#include "CheckMethod.h"

class KeyChecker : public IKeyChecker, public ICheckMethodsManager, public ICheckMethodsViewer {
	public:
		KeyChecker(void);
		~KeyChecker(void);

		const std::shared_ptr<const CheckMethod> create_check_method_base(void) const;
		const std::shared_ptr<const CheckMethod> create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key) const;
		const std::shared_ptr<const CheckMethod> create_check_method_memory(const offset_t offset, std::vector<const byte_t>& value, std::shared_ptr<const CheckMethod> logged_in_method) const;
	protected:
		mutable std::vector<std::shared_ptr<const CheckMethod>> m_check_methods;

		virtual const bool check(void) const = 0;
		virtual void set_max_check_number(check_number_t check_number) const final;
		virtual void logout(const bool forced_logout) const;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const override = 0;
		virtual const bool is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
		virtual const bool is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const override = 0;
		virtual const bool logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override = 0;
	private:
		std::map<const std::shared_ptr<const CheckMethodLogin>, const handle_t> m_handles;
};
