
#ifndef __IPROTECTKEYDELEGATE_H__
#define __IPROTECTKEYDELEGATE_H__

class IProtectKeyDelegate {
	public:
		IProtectKeyDelegate(void);

		virtual void did_check_protect_key(const bool success) = 0;
	protected:
		virtual ~IProtectKeyDelegate(void);
};

#endif // #define __IPROTECTKEYDELEGATE_H__

