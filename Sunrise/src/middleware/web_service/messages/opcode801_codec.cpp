#include "opcode801.h"

#include <cstring>

namespace sunrise::middleware::web_service::messages::opcode801 {

[[nodiscard]] bool parse_request(const Message& message, Request& request) noexcept {
    request = {};

    // opcode801 payload: 8 bytes for subclassInstanceSoid + 1 byte for socketEntry = 9 bytes minimum
    if (message.payload.size() < 9) {
        return false;
    }

    // Parse the 8-byte subclass instance SOID (little-endian)
    std::memcpy(&request.subclassInstanceSoid, message.payload.data(), sizeof(std::uint64_t));

    // Parse the 1-byte socket entry index
    request.socketEntry = std::to_integer<std::uint8_t>(message.payload[8]);

    return true;
}

} // namespace sunrise::middleware::web_service::messages::opcode801
