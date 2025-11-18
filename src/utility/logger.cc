#include "utility/logger.h"

namespace pbr {

std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> Logger::console_sink_;
std::shared_ptr<spdlog::sinks::basic_file_sink_mt> Logger::file_sink_;
std::shared_ptr<spdlog::logger> Logger::logger_;


void Logger::Init() {
  console_sink_ = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink_->set_level(spdlog::level::trace);
  console_sink_->set_pattern(">>> %^[%L] %v%$");

  file_sink_ =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true);
  file_sink_->set_level(spdlog::level::trace);
  file_sink_->set_pattern(">>> [%l] [%c] %v");

  logger_ = std::make_shared<spdlog::logger>(
      "pbr_logger", spdlog::sinks_init_list{console_sink_, file_sink_});

  logger_->set_level(spdlog::level::trace);
  logger_->info("Logger initialised!");
}

}  // namespace pbr