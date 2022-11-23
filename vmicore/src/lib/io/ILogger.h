#ifndef VMICORE_ILOGGER_H
#define VMICORE_ILOGGER_H

#include "RustStr.h"
#include <cxxbridge/rust/cxx.h>
#include <cxxbridge/rust_grpc_server/src/bridge.rs.h>
#include <memory>
#include <string_view>

namespace VmiCore
{
    // Has to be the same as in the HiveOperations project to indicate in which file the log should be written.
    // pkg->script->vmi->vmi_connector.go
    constexpr auto WRITE_TO_FILE_TAG = "writeToFileTag";

    namespace logfield
    {
        inline ::rust::Box<::logging::LogField> create(std::string_view key, std::string_view val)
        {
            return ::logging::field_str(toRustStr(key), toRustStr(val));
        }

        inline ::rust::Box<::logging::LogField> create(std::string_view key, const char* val)
        {
            return ::logging::field_str(toRustStr(key), val);
        }

        inline ::rust::Box<::logging::LogField> create(std::string_view key, const bool& val)
        {
            return ::logging::field_bool(toRustStr(key), val);
        }

        inline ::rust::Box<::logging::LogField> create(std::string_view key, const int64_t& val)
        {
            return ::logging::field_i64(toRustStr(key), val);
        }

        inline ::rust::Box<::logging::LogField> create(std::string_view key, const uint64_t& val)
        {
            return ::logging::field_uint64(toRustStr(key), val);
        }

        inline ::rust::Box<::logging::LogField> create(std::string_view key, const double& val)
        {
            return ::logging::field_float64(toRustStr(key), val);
        }
    }

    class ILogger
    {
      public:
        virtual ~ILogger() = default;
        virtual void bind(const std::initializer_list<rust::Box<::logging::LogField>>& fields) = 0;

        virtual void debug(std::string_view message) const = 0;
        virtual void debug(std::string_view message,
                           const std::initializer_list<rust::Box<::logging::LogField>>& fields) const = 0;

        virtual void info(std::string_view message) const = 0;
        virtual void info(std::string_view message,
                          const std::initializer_list<rust::Box<::logging::LogField>>& fields) const = 0;

        virtual void warning(std::string_view message) const = 0;
        virtual void warning(std::string_view message,
                             const std::initializer_list<rust::Box<::logging::LogField>>& fields) const = 0;

        virtual void error(std::string_view message) const = 0;
        virtual void error(std::string_view message,
                           const std::initializer_list<rust::Box<::logging::LogField>>& fields) const = 0;

      protected:
        ILogger() = default;
    };
}

#endif // VMICORE_ILOGGER_H