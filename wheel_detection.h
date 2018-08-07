#ifndef _WHEEL_DETECTION_H
#define _WHEEL_DETECTION_H

#include <stdint.h>

typedef struct{
	uint32_t wheel_detection_threshold;
	uint32_t wheel_detection_base_line;
	uint32_t sensor_value;
	uint32_t wheel_count;
	uint8_t wheel_detection_started;
	uint8_t train_detected;
	uint32_t wheel_on_top_timer;
	uint32_t total_detection_timer;
	uint32_t sensor_not_detecting_timer;
} WHEEL_SENSOR;

uint8_t probe_wheel_detection(WHEEL_SENSOR *channel);
void initialize_sensor_data_structure(WHEEL_SENSOR* curr_chan);

#endif
