#pragma once

// Number of analog numbers.
#define INPUT_NUM 4

// Number of bytes per message.
#define MSG_SIZE INPUT_NUM

#define MAX_SERVO_CHANNELS 4
#define MAX_JOYSTICK_INPUTS MAX_SERVO_CHANNELS

uint16_t input_pin[MAX_JOYSTICK_INPUTS] = { PA0, PA1, PA4, PA5 };

static_assert(INPUT_NUM <= MAX_SERVO_CHANNELS);