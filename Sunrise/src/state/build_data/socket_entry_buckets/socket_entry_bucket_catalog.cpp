#include "socket_entry_bucket_catalog.h"

#include <algorithm>
#include <span>

namespace sunrise::state::build_data::socket_entry_buckets {

namespace {

/** Fixed storage for resolved socket-entry-bucket mappings. */
std::array<Definition, kDefinitionCapacity> g_definitions{};

/** Number of published socket-entry-bucket definitions. */
std::size_t g_count = 0;

} // namespace

void clear() noexcept {
    g_definitions = {};
    g_count = 0;
}

[[nodiscard]] bool valid(std::span<const Definition> definitions) noexcept {
    if (definitions.size() > kDefinitionCapacity) {
        return false;
    }

    // Verify no duplicates
    for (std::size_t i = 0; i < definitions.size(); ++i) {
        for (std::size_t j = i + 1; j < definitions.size(); ++j) {
            if (definitions[i].socketEntryListIndex == definitions[j].socketEntryListIndex) {
                return false;
            }
        }
    }

    return true;
}

[[nodiscard]] bool replace(std::span<const Definition> definitions) noexcept {
    if (!valid(definitions)) {
        return false;
    }

    clear();
    if (definitions.empty()) {
        return true;
    }

    std::copy(definitions.begin(), definitions.end(), g_definitions.begin());
    g_count = definitions.size();
    return true;
}

[[nodiscard]] bool find(std::uint16_t socketEntryListIndex, Definition& definition) noexcept {
    for (std::size_t i = 0; i < g_count; ++i) {
        if (g_definitions[i].socketEntryListIndex == socketEntryListIndex) {
            definition = g_definitions[i];
            return true;
        }
    }
    return false;
}

[[nodiscard]] std::size_t count() noexcept {
    return g_count;
}

} // namespace sunrise::state::build_data::socket_entry_buckets
