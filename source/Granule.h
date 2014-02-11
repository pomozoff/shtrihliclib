
#pragma once

#include "KeyChecker.h"
#include "ProtectKey.h"

class Granule final : public KeyChecker, public std::enable_shared_from_this<const Granule> {
	public:
		Granule(const std::string id, const protect_key_t protect_key);
		~Granule(void);
	
		virtual const bool check(void) const override final;

		void set_granule_nfr_date(bool is_granule_nfr_date);
		const bool is_granule_nfr_date(void) const;
	protected:
	private:
		const std::string _id = R"()";
		const protect_key_t _protect_key = nullptr;
		bool _is_granule_nfr_date = false;
};
