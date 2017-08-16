/******************************************************
 *				Robert Bosch Ltda                     *
 ******************************************************/
 
 /**
 * @file jsn_sr04t.h
 * @author Anderson Felippe <anderson.felippe@br.bosch.com>
 * @date 09 Aug 2017
 * @brief Header to file to control JSN's JSN-SR04T-2.0 waterproof ultrasound board + sensor
 *
 * Controlling functions for the JSN-SR04T-2.0 board
 */
	
#ifndef _JSN_SR04T_H
#define _JSN_SR04T_H

//---- Sensors ----//
#define SENSOR1				1	// Points to ultrasound sensor 1
#define SENSOR2				2	// Points to ultrasound sensor 2
#define SENSOR3				3	// Points to ultrasound sensor 3
#define SENSOR4				4	// Points to ultrasound sensor 4
//---- Pins ----//
#define ECHOPIN_SENSOR1		2     // Pin to receive echo pulse
#define TRIGPIN_SENSOR1     3     // Pin to send trigger pulse
#define ECHOPIN_SENSOR2		4     // Pin to receive echo pulse
#define TRIGPIN_SENSOR2     5     // Pin to send trigger pulse
#define ECHOPIN_SENSOR3		6     // Pin to receive echo pulse
#define TRIGPIN_SENSOR3     7     // Pin to send trigger pulse
#define ECHOPIN_SENSOR4		8     // Pin to receive echo pulse
#define TRIGPIN_SENSOR4     9     // Pin to send trigger pulse
//---- Rates ----//
#define CALIBRATION_RATE    100   // Calibration rate to calculate average

//Initialize all sensors
void init_ultrasound_sensors(void);
// Calibrates given ultrasound sensor 
void calibrate_ultrasound_sensor(uint8_t);
// Call calibration to all sensors
void calibrate_all_sensors(void);
// Get distance from a given sensor
int16_t get_distance(uint8_t);

#endif /* _JSN_SR04T_H */