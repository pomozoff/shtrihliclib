
#pragma once

#include <memory>
#include <vector>
#include <map>

#include "IKeyChecker.h"
#include "ICheckMethodsManager.h"
#include "ICheckMethodsViewer.h"
#include "CheckMethod.h"

class KeyChecker : public IKeyChecker, ICheckMethodsManager, ICheckMethodsViewer {
	public:
		KeyChecker(void);
		~KeyChecker(void);

		std::shared_ptr<CheckMethod> create_check_method_base(void) const;
		std::shared_ptr<CheckMethod> create_check_method_login(const feature_t feature, const bool allow_to_login_on_previous_key) const;
		std::shared_ptr<CheckMethod> create_check_method_memory(const offset_t offset, std::vector<byte_t>& value, std::shared_ptr<CheckMethod> logged_in_method) const;
	protected:
		virtual void set_max_check_number(check_number_t check_number) const final;
	private:
		mutable std::vector<std::shared_ptr<CheckMethod>> m_check_methods;
		std::map<std::shared_ptr<CheckMethodLogin>, handle_t> m_handles;

		/* IKeyChecker Interface */
		virtual const bool is_base_key_available(const std::shared_ptr<const CheckMethodBase> checkMethod) const override;
		virtual const bool is_able_to_login(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
		virtual const bool is_same_memory(const std::shared_ptr<const CheckMethodMemory> checkMethod) const override;
		virtual const bool logout_key(const std::shared_ptr<const CheckMethodLogin> checkMethod) const override;
};
