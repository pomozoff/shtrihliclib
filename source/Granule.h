
#pragma once

#include "KeyChecker.h"

class ProtectKey;

class Granule final : public KeyChecker, public std::enable_shared_from_this<const Granule> {
	public:
		Granule(const std::string id, const std::shared_ptr<const ProtectKey> protect_key);
		~Granule(void);
	
		virtual const bool check(void) const override final;

		void set_granule_nfr_date(bool is_granule_nfr_date);
		const bool is_granule_nfr_date(void) const;
	protected:
	private:
		const std::string _id;
		const std::shared_ptr<const ProtectKey> _protect_key;
		bool _is_granule_nfr_date;
};
