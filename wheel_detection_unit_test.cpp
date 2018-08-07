#include <limits.h>
#include "wheel_detection.h"
#include "gtest/gtest.h"
namespace {

TEST(WheelDetector, InitializeStructure)
{
	/* Channel structure should be properly initialized */
	WHEEL_SENSOR curr_chan;
	initialize_sensor_data_structure(&curr_chan);

	EXPECT_EQ(0, curr_chan.wheel_detection_threshold);
	EXPECT_EQ(0, curr_chan.wheel_detection_base_line);
	EXPECT_EQ(0, curr_chan.sensor_value);
	EXPECT_EQ(0, curr_chan.wheel_count);
	EXPECT_EQ(0, curr_chan.wheel_detection_started);
	EXPECT_EQ(0, curr_chan.train_detected);
	EXPECT_EQ(0, curr_chan.wheel_on_top_timer);
	EXPECT_EQ(0, curr_chan.total_detection_timer);
	EXPECT_EQ(0, curr_chan.sensor_not_detecting_timer);
}

TEST(WheelDetector, DetectFirstTrainWheel)
{
	/* Detect the wheel for the first time and set internal flags */
	WHEEL_SENSOR curr_chan;
	initialize_sensor_data_structure(&curr_chan);

	curr_chan.wheel_detection_threshold = 10;
	curr_chan.wheel_detection_base_line = 100;
	curr_chan.sensor_value = 120;

	probe_wheel_detection(&curr_chan);
	
	EXPECT_EQ(10, curr_chan.wheel_detection_threshold);
	EXPECT_EQ(100, curr_chan.wheel_detection_base_line);
	EXPECT_EQ(120, curr_chan.sensor_value);
	EXPECT_EQ(1, curr_chan.wheel_count);
	EXPECT_EQ(1, curr_chan.wheel_detection_started);
	EXPECT_EQ(1, curr_chan.train_detected);
	EXPECT_EQ(1, curr_chan.wheel_on_top_timer);
	EXPECT_EQ(1, curr_chan.total_detection_timer);
	EXPECT_EQ(0, curr_chan.sensor_not_detecting_timer);	
}

TEST(WheelDetector, wheel_not_available_scenario1)
{
	/* Check whether firmware operates properly when wheel is not on the sensor */
	WHEEL_SENSOR curr_chan;
	initialize_sensor_data_structure(&curr_chan);

	curr_chan.wheel_detection_threshold = 10;
	curr_chan.wheel_detection_base_line = 100;
	curr_chan.sensor_value = 100;

	probe_wheel_detection(&curr_chan);
	
	EXPECT_EQ(10, curr_chan.wheel_detection_threshold);
	EXPECT_EQ(100, curr_chan.wheel_detection_base_line);
	EXPECT_EQ(100, curr_chan.sensor_value);
	EXPECT_EQ(0, curr_chan.wheel_count);
	EXPECT_EQ(0, curr_chan.wheel_detection_started);
	EXPECT_EQ(0, curr_chan.train_detected);
	EXPECT_EQ(0, curr_chan.wheel_on_top_timer);
	EXPECT_EQ(0, curr_chan.total_detection_timer);
	EXPECT_EQ(1, curr_chan.sensor_not_detecting_timer);	
}

TEST(WheelDetector, sensor_not_detecting_timer_test)
{
	/* Timer used to track sensor idleing is working or not */
	WHEEL_SENSOR curr_chan;
	initialize_sensor_data_structure(&curr_chan);

	curr_chan.wheel_detection_threshold = 10;
	curr_chan.wheel_detection_base_line = 100;
	curr_chan.sensor_value = 100;

	probe_wheel_detection(&curr_chan);
	probe_wheel_detection(&curr_chan);	
	
	EXPECT_EQ(10, curr_chan.wheel_detection_threshold);
	EXPECT_EQ(100, curr_chan.wheel_detection_base_line);
	EXPECT_EQ(100, curr_chan.sensor_value);
	EXPECT_EQ(0, curr_chan.wheel_count);
	EXPECT_EQ(0, curr_chan.wheel_detection_started);
	EXPECT_EQ(0, curr_chan.train_detected);
	EXPECT_EQ(0, curr_chan.wheel_on_top_timer);
	EXPECT_EQ(0, curr_chan.total_detection_timer);
	EXPECT_EQ(2, curr_chan.sensor_not_detecting_timer);	
}

TEST(WheelDetector, wheel_on_top_timer_test)
{
	/* Wheel on top of sensor for more than one conscutive time period */
	WHEEL_SENSOR curr_chan;
	initialize_sensor_data_structure(&curr_chan);

	curr_chan.wheel_detection_threshold = 10;
	curr_chan.wheel_detection_base_line = 100;
	curr_chan.sensor_value = 120;

	probe_wheel_detection(&curr_chan);
	probe_wheel_detection(&curr_chan);
	
	EXPECT_EQ(10, curr_chan.wheel_detection_threshold);
	EXPECT_EQ(100, curr_chan.wheel_detection_base_line);
	EXPECT_EQ(120, curr_chan.sensor_value);
	EXPECT_EQ(1, curr_chan.wheel_count);
	EXPECT_EQ(1, curr_chan.wheel_detection_started);
	EXPECT_EQ(1, curr_chan.train_detected);
	EXPECT_EQ(2, curr_chan.wheel_on_top_timer);
	EXPECT_EQ(2, curr_chan.total_detection_timer);
	EXPECT_EQ(0, curr_chan.sensor_not_detecting_timer);	
}

}
