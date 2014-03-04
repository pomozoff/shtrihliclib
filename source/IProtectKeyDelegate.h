
#pragma once

class IProtectKeyDelegate {
	public:
		IProtectKeyDelegate(void);

		virtual void did_check_protect_key(bool success) const = 0;
	protected:
		virtual ~IProtectKeyDelegate(void);
};
