
#ifndef __REALKEYROCKEYNET_H__
#define __REALKEYROCKEYNET_H__

#include "RealKeyRockey.h"
#include <windows.h>

class RealKeyRockeyNet : public RealKeyRockey {
	public:
		RealKeyRockeyNet(char* ini_path);
		virtual ~RealKeyRockeyNet(void);

		RealKeyRockeyNet& RealKeyRockeyNet::operator=(const RealKeyRockeyNet& other);
		RealKeyRockeyNet& RealKeyRockeyNet::operator=(RealKeyRockeyNet&& other);
	protected:
		RealKeyRockeyNet(void);

		virtual const size_t max_memory_size(void) const;

		virtual const rockey_long_t prepared_feature_id(const rockey_feature_t feature_id) const override;
		virtual const uint16_t call_rockey(uint16_t function, uint16_t* handle, uint32_t* lp1, uint32_t* lp2, uint16_t* p1, uint16_t* p2, uint16_t* p3, uint16_t* p4, uint8_t* buffer) const override;
	private:
		static const size_t _key_type = 6;
		static const size_t _memory_size = 120;

		const bool _is_terminal_mode;
		const HINSTANCE _library_handle;
		const FARPROC _net_rockey_function_pointer;
		const FARPROC _set_ini_path_function_pointer;

		const bool is_terminal_mode_detected(void) const;

		const HINSTANCE load_library(const LPCWCH library_name) const;
		const FARPROC get_function_pointer(const HINSTANCE library_handle, const char* function_name) const;
};

#endif // __REALKEYROCKEYNET_H__
