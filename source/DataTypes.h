
#ifndef __DATATYPES_H__
#define __DATATYPES_H__

#include <stdint.h>
#include <vector>
#include <memory>

enum class KeyMemoryType { ReadOnly, ReadWrite };

using byte_t = uint8_t;
using status_t = uint32_t;
using offset_t = uint32_t;
using feature_t = uint32_t;
using key_handle_t = int32_t;

using features_t = std::vector<const feature_t>;

using check_number_t = unsigned int;

class IKeyChecker;
class CheckMethod;
class CheckMethodBase;
class CheckMethodLogin;
class CheckMethodMemory;
class Platform;
class LicenseBlock;
class LicenseBlockManager;
class RealKeyHasp;
class RealKeyHaspSL;
class RealKeyRockey;

using value_t = std::vector<const byte_t>;
using ikey_checker_t = std::shared_ptr<const IKeyChecker>;
using check_method_t = std::shared_ptr<const CheckMethod>;
using check_method_base_t = std::shared_ptr<const CheckMethodBase>;
using check_method_login_t = std::shared_ptr<const CheckMethodLogin>;
using check_method_memory_t = std::shared_ptr<const CheckMethodMemory>;
using check_methods_memory_t = std::vector<const check_method_memory_t>;
using platform_t = std::shared_ptr<const Platform>;
using license_block_t = std::shared_ptr<const LicenseBlock>;
using license_blocks_t = std::vector<const license_block_t>;
using license_block_manager_t = std::shared_ptr<const LicenseBlockManager>;
using real_key_hasp_t = std::shared_ptr<const RealKeyHasp>;
using real_key_hasp_sl_t = std::shared_ptr<const RealKeyHaspSL>;
using real_key_rockey_t = std::shared_ptr<const RealKeyRockey>;

#endif // __DATATYPES_H__
