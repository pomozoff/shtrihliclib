
#pragma once

#include <stdint.h>
#include <vector>
#include <memory>

using byte_t = uint8_t;
using offset_t = uint32_t;
using feature_t = uint32_t;
using handle_t = uint32_t;

using check_number_t = unsigned int;

class IKeyChecker;
class CheckMethod;
class CheckMethodBase;
class CheckMethodLogin;
class CheckMethodMemory;
class Platform;

using value_t = std::vector<const byte_t>;
using ikey_checker_t = std::shared_ptr<const IKeyChecker>;
using check_method_t = std::shared_ptr<const CheckMethod>;
using check_method_base_t = std::shared_ptr<const CheckMethodBase>;
using check_method_login_t = std::shared_ptr<const CheckMethodLogin>;
using check_method_memory_t = std::shared_ptr<const CheckMethodMemory>;
using platform_t = std::shared_ptr<const Platform>;
