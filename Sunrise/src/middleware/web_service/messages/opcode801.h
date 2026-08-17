#pragma once

#include <cstdint>

#include "../web_service_envelope.h"

namespace sunrise::middleware::web_service::messages::opcode801 {

/** Web Service opcode for the subclass-selection request. */
inline constexpr std::uint16_t kOpcode = 801;

/** The subclass instance and selected socket entry index. */
struct Request {
    std::uint64_t subclassInstanceSoid{};
    std::uint8_t socketEntry{};
};

/**
 * Parses the opcode-801 subclass-selection request.
 * @param message Parsed Web Service envelope.
 * @param request Receives the decoded subclass instance and socket entry.
 * @return True when the request is complete and valid.
 */
[[nodiscard]] bool parse_request(const Message& message, Request& request) noexcept;

} // namespace sunrise::middleware::web_service::messages::opcode801
