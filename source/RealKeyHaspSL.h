
#pragma once

#include "RealKeyHasp.h"

class RealKeyHaspSL : public RealKeyHasp {
	public:
		RealKeyHaspSL(void);
		virtual ~RealKeyHaspSL(void);

		/* RealKeyHasp Interface */
		virtual const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const override;
};
