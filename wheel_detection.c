#include <stdio.h>
#include "wheel_detection.h"


static void wheel_detection_not_started(void);
static void wheel_detection_in_progress(void);
static void wheel_counter_count_up(void);
static void reset_total_detection_timer(void);
static void reset_wheel_on_top_timer(void);
static void reset_sensor_not_detecting_timer(void);

static WHEEL_SENSOR *channel;


void
initialize_sensor_data_structure(WHEEL_SENSOR* curr_chan)
{
	curr_chan->wheel_detection_threshold = 0U;
	curr_chan->wheel_detection_base_line = 0U;
	curr_chan->sensor_value = 0U;
	curr_chan->wheel_count = 0U;
	curr_chan->wheel_detection_started = 0U;
	curr_chan->train_detected = 0U;
	curr_chan->wheel_on_top_timer = 0U;
	curr_chan->total_detection_timer = 0U;
	curr_chan->sensor_not_detecting_timer = 0U;
}

uint8_t
probe_wheel_detection(WHEEL_SENSOR* curr_chn)
{
	int32_t diff = 0U;

	channel = curr_chn;

	/* Get the difference from the base line */
	diff = channel->sensor_value - channel->wheel_detection_base_line;

	if(diff < 0){
		diff = diff * (-1);
	}

	//printf("diff: %d\n\r",diff);

	/* Compare the value difference with the threshold */
	if(diff >= channel->wheel_detection_threshold){

		/* Did last sample also detect a train wheel */
		if(channel->wheel_detection_started == 0U){
			wheel_detection_not_started();
		}
		else{
			wheel_detection_in_progress();
		}

		/* Is this a new train? */
		if(channel->train_detected == 0U){
			reset_total_detection_timer();
			channel->train_detected = 1U;
		}
		
		channel->total_detection_timer++;
	}
	else{
		/* Train wheel is not on the sensor */
		channel->wheel_detection_started = 0U;
		channel->sensor_not_detecting_timer++;
	}
	
	return 0;
}

static void
wheel_detection_not_started(void)
{
	//printf("%s\n\r",__FUNCTION__);
	reset_wheel_on_top_timer();
	reset_sensor_not_detecting_timer();
	wheel_counter_count_up();

	channel->wheel_detection_started = 1U;
	channel->wheel_on_top_timer++;
}

static void
wheel_detection_in_progress(void)
{
	//printf("%s\n\r",__FUNCTION__);
	channel->wheel_on_top_timer++;
}

static void
wheel_counter_count_up(void)
{
	channel->wheel_count++;
}

static void
reset_total_detection_timer(void)
{
	channel->total_detection_timer = 0U;
}

static void 
reset_wheel_on_top_timer(void)
{
	channel->wheel_on_top_timer = 0U;
}

static void
reset_sensor_not_detecting_timer(void)
{
	channel->sensor_not_detecting_timer = 0U;
}

