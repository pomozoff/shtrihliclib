
#ifndef __REALKEYHASPHL_H__
#define __REALKEYHASPHL_H__

#include "RealKeyHasp.h"

class RealKeyHaspHL : public RealKeyHasp {
	public:
		RealKeyHaspHL(void);
		virtual ~RealKeyHaspHL(void);

		/* RealKeyHasp Interface */
		virtual const hasp_status_t _hasp_login_scope(const hasp_feature_t feature_id, const char* scope, const hasp_vendor_code_t vendor_code, hasp_handle_t& handle) const override;
};

#endif // __REALKEYHASPHL_H__
