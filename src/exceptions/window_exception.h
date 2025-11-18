#ifndef SRC_EXCEPTIONS_WINDOWEXCEPTION_H_
#define SRC_EXCEPTIONS_WINDOWEXCEPTION_H_

#include "pbr_api.h"
#include <exception>

namespace pbr {
class PBR_API WindowException : public std::exception {
 public:
  WindowException(const char* message) : message_(message) {};
  const char* what() const noexcept { return message_; }

 private:
  const char* message_;
};
}  // namespace pbr

#endif  // SRC_EXCEPTIONS_WINDOWEXCEPTION_H_