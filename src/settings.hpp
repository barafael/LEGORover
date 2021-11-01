#pragma once

// Number of channels.
constexpr const size_t CHANNEL_COUNT = 4;

// Number of bytes per message.
constexpr const size_t PAYLOAD_SIZE = CHANNEL_COUNT;

// Maximum number of channels.
constexpr const size_t MAX_CHANNEL_COUNT = 8;

// Assert that channel count is valid.
static_assert(CHANNEL_COUNT <= MAX_CHANNEL_COUNT);

// Loop delay in milliseconds.
constexpr const size_t LOOP_DELAY_MS = 50;
