#pragma once

#define BOARD_V1
#ifdef BOARD_V1

#include <cstddef>
#include <cstdint>

#include <Arduino.h>

#include "settings.hpp"

constexpr const uint16_t HC12_RX = PA3;
constexpr const uint16_t HC12_TX = PA2;

constexpr const uint16_t HC12_SET_PIN = PB10;

constexpr const uint16_t UART_RX = PA10;
constexpr const uint16_t UART_TX = PA9;

constexpr const uint16_t ANALOG_INPUTS[MAX_CHANNEL_COUNT] = { PA0, PA1, PA4, PA5, PA6, PA7, PB0, PB1 };

constexpr const uint16_t SERVO_OUTPUTS[MAX_CHANNEL_COUNT] = {
    PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15,
};

#endif // BOARD_V1
