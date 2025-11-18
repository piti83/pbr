#ifndef SRC_UTILITY_LOGGER_H_
#define SRC_UTILITY_LOGGER_H_

#include "pbr_api.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>
#include <format>

namespace pbr {

class PBR_API Logger {
 public:
  Logger() = delete;

  static void Init();

  template<typename... Args>
  static void Trace(spdlog::format_string_t<Args...> fmt, Args&&... args) {
    logger_->trace(fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void Debug(spdlog::format_string_t<Args...> fmt, Args&&... args) {
    logger_->debug(fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void Info(spdlog::format_string_t<Args...> fmt, Args&&... args) {
    logger_->info(fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void Warn(spdlog::format_string_t<Args...> fmt, Args&&... args) {
    logger_->warn(fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void Error(spdlog::format_string_t<Args...> fmt, Args&&... args) {
    logger_->error(fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void Critical(spdlog::format_string_t<Args...> fmt, Args&&... args) {
    logger_->critical(fmt, std::forward<Args>(args)...);
  }

 private:
  static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink_;
  static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> file_sink_;
  static std::shared_ptr<spdlog::logger> logger_;
};

}  // namespace pbr

#endif  // SRC_UTILITY_LOGGER_H_