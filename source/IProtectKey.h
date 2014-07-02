
#ifndef __IPROTECTKEY_H__
#define __IPROTECTKEY_H__

#include "DataTypes.h"

class Granule;
using granule_t = std::shared_ptr<const Granule>;

class IProtectKey {
	public:
		virtual ~IProtectKey(void);

		virtual const bool check_license(void) const = 0;
		virtual const bool is_key_nfr(void) const = 0;
		virtual const bool is_key_base(void) const = 0;

		virtual const time_t check_license_timeout(void) const = 0;
		virtual const granule_t granule_with_name(const std::wstring& granule_name) const = 0;
		virtual const time_t get_nfr_end_date(void) const = 0;

		//virtual const bool decrypt(byte_t* buffer, const size_t length) const = 0;
		virtual void encrypt(const byte_t* input_buffer, const size_t input_length, byte_t** iv_enc, size_t& iv_length, byte_t** encrypted_buffer, size_t& encrypted_length) const = 0;
		virtual void decrypt(const byte_t* encrypted_buffer, const size_t encrypted_length, byte_t* iv_dec, byte_t** decrypted_buffer) const = 0;

		void set_decrypt_method(const check_method_login_t decrypt_method) const;
	protected:
		IProtectKey(void);

		mutable check_method_login_t _decrypt_method = nullptr;
};

#endif // __IPROTECTKEY_H__
