/******************************************************
 *				Robert Bosch Ltda                     *
 ******************************************************/
 
 /**
 * @file jsn_sr04t.cpp
 * @author Anderson Felippe <anderson.felippe@br.bosch.com>
 * @date 09 Aug 2017
 * @brief Header to file to control JSN's JSN-SR04T-2.0 waterproof ultrasound board + sensor
 *
 * Controlling functions for the JSN-SR04T-2.0 board
 */

#include "Arduino.h"
#include "jsn_sr04t.h"
 
static uint16_t calibrated_average_1 = 0;
static uint16_t calibrated_average_2 = 0;
static uint16_t calibrated_average_3 = 0;
static uint16_t calibrated_average_4 = 0;
static float upper_detection_trigger_1 = 0;
static float lower_detection_trigger_1 = 0;
static float upper_detection_trigger_2 = 0;
static float lower_detection_trigger_2 = 0; 
static float upper_detection_trigger_3 = 0;
static float lower_detection_trigger_3 = 0; 
static float upper_detection_trigger_4 = 0;
static float lower_detection_trigger_4 = 0;
static uint16_t distance[4];

// Private prototypes
// Get configured echo pin for given sensor
uint8_t get_echo_pin(uint8_t);
// Get configured trigger pin for given sensor
uint8_t get_trigger_pin(uint8_t);

void init_ultrasound_sensors()
{
	Serial.println("Initializing sensors...\n");
	pinMode(ECHOPIN_SENSOR1, INPUT_PULLUP);
	pinMode(TRIGPIN_SENSOR1, OUTPUT);
	pinMode(ECHOPIN_SENSOR2, INPUT_PULLUP);
	pinMode(TRIGPIN_SENSOR2, OUTPUT);
	pinMode(ECHOPIN_SENSOR3, INPUT_PULLUP);
	pinMode(TRIGPIN_SENSOR3, OUTPUT);
	pinMode(ECHOPIN_SENSOR4, INPUT_PULLUP);
	pinMode(TRIGPIN_SENSOR4, OUTPUT);
	//Small delay before sensor hardware initialization
	delay(20);
	Serial.println("Initialization complete.\n");
}


void calibrate_ultrasound_sensor(uint8_t sensor_number)
{
	uint8_t i;
	int distance = 0;
	int distance_tmp = 0;
	calibrated_average_1 = 0;
	calibrated_average_2 = 0;
	calibrated_average_3 = 0;
	calibrated_average_4 = 0;
	Serial.print("\nCalibrating ultrasound sensor ");
	Serial.print(sensor_number);
	Serial.println("...");
	
	// Acquire sensor static values to form a calibration
	for (i = 0; i < CALIBRATION_RATE; i++)
	{
		switch(sensor_number)
		{
			case SENSOR1:
				digitalWrite(TRIGPIN_SENSOR1, LOW); // Set the trigger pin to low for 2uS
				delayMicroseconds(2);
				digitalWrite(TRIGPIN_SENSOR1, HIGH); // Send a 10uS high to trigger ranging
				delayMicroseconds(10);
				digitalWrite(TRIGPIN_SENSOR1, LOW); // Send pin low again
				distance_tmp = pulseIn(ECHOPIN_SENSOR1, HIGH, 26000); // Read in times pulse
				if (distance_tmp > 0)
				{
					distance = distance_tmp;
				}
				distance /= 58;
				calibrated_average_1 += distance;
				delay(50);// Wait 50mS before next ranging
				break;
				
			case SENSOR2:
				digitalWrite(TRIGPIN_SENSOR2, LOW); // Set the trigger pin to low for 2uS
				delayMicroseconds(2);
				digitalWrite(TRIGPIN_SENSOR2, HIGH); // Send a 10uS high to trigger ranging
				delayMicroseconds(10);
				digitalWrite(TRIGPIN_SENSOR2, LOW); // Send pin low again
				distance_tmp = pulseIn(ECHOPIN_SENSOR2, HIGH, 26000); // Read in times pulse
				if (distance_tmp > 0)
				{
					distance = distance_tmp;
				}
				distance /= 58;
				calibrated_average_2 += distance;
				delay(50);// Wait 50mS before next ranging
				break;
				
			case SENSOR3:
				digitalWrite(TRIGPIN_SENSOR3, LOW); // Set the trigger pin to low for 2uS
				delayMicroseconds(2);
				digitalWrite(TRIGPIN_SENSOR3, HIGH); // Send a 10uS high to trigger ranging
				delayMicroseconds(10);
				digitalWrite(TRIGPIN_SENSOR3, LOW); // Send pin low again
				distance_tmp = pulseIn(ECHOPIN_SENSOR3, HIGH, 26000); // Read in times pulse
				if (distance_tmp > 0)
				{
					distance = distance_tmp;
				}
				distance /= 58;
				calibrated_average_3 += distance;
				delay(50);// Wait 50mS before next ranging
				break;
				
			case SENSOR4:
				digitalWrite(TRIGPIN_SENSOR4, LOW); // Set the trigger pin to low for 2uS
				delayMicroseconds(2);
				digitalWrite(TRIGPIN_SENSOR4, HIGH); // Send a 10uS high to trigger ranging
				delayMicroseconds(10);
				digitalWrite(TRIGPIN_SENSOR4, LOW); // Send pin low again
				distance_tmp = pulseIn(ECHOPIN_SENSOR4, HIGH, 26000); // Read in times pulse
				if (distance_tmp > 0)
				{
					distance = distance_tmp;
				}
				distance /= 58;
				calibrated_average_4 += distance;
				delay(50);// Wait 50mS before next ranging
				break;
			
			default:
				Serial.println("Invalid sensor number. Can't calibrate.");
				break;
		}
	}
	// Get calibrated average based on rate set and calculate detection triggers
	switch(sensor_number)
	{
		case SENSOR1:
			calibrated_average_1 /= CALIBRATION_RATE;
			// Calibration check
			if (calibrated_average_1 == 0)
			{
				Serial.println("\n<ERROR> Failed to calibrate sensor 1.");
				Serial.println("\tRemove any objects closer than 15cm.");
				Serial.println("\tDouble check sensor pins connections.");
				return;
			}
			upper_detection_trigger_1 = (float)calibrated_average_1 * (1.0 + DETECTION_RATE);
			lower_detection_trigger_1 = (float)calibrated_average_1 * (1.0 - DETECTION_RATE);
			Serial.print("Calibration done to sensor 1: ");
			Serial.print(calibrated_average_1);
			Serial.println(" cm");
			break;
			
		case SENSOR2:
			calibrated_average_2 /= CALIBRATION_RATE;
			// Calibration check
			if (calibrated_average_2 == 0)
			{
				Serial.println("\n<ERROR> Failed to calibrate sensor 2.");
				Serial.println("\tRemove any objects closer than 15cm.");
				Serial.println("\tDouble check sensor pins connections.");
				return;
			}
			upper_detection_trigger_2 = (float)calibrated_average_2 * (1.0 + DETECTION_RATE);
			lower_detection_trigger_2 = (float)calibrated_average_2 * (1.0 - DETECTION_RATE);
			Serial.print("Calibration done to sensor 2: ");
			Serial.print(calibrated_average_2);
			Serial.println(" cm");
			break;
		
		case SENSOR3:
			calibrated_average_3 /= CALIBRATION_RATE;
			// Calibration check
			if (calibrated_average_3 == 0)
			{
				Serial.println("\n<ERROR> Failed to calibrate sensor 3.");
				Serial.println("\tRemove any objects closer than 15cm.");
				Serial.println("\tDouble check sensor pins connections.");
				return;
			}
			upper_detection_trigger_3 = (float)calibrated_average_3 * (1.0 + DETECTION_RATE);
			lower_detection_trigger_3 = (float)calibrated_average_3 * (1.0 - DETECTION_RATE);
			Serial.print("Calibration done to sensor 3: ");
			Serial.print(calibrated_average_3);
			Serial.println(" cm");
			break;
		
		case SENSOR4:
			calibrated_average_4 /= CALIBRATION_RATE;
			// Calibration check
			if (calibrated_average_4 == 0)
			{
				Serial.println("\n<ERROR> Failed to calibrate sensor 4.");
				Serial.println("\tRemove any objects closer than 15cm.");
				Serial.println("\tDouble check sensor pins connections.");
				return;
			}
			upper_detection_trigger_4 = (float)calibrated_average_4 * (1.0 + DETECTION_RATE);
			lower_detection_trigger_4 = (float)calibrated_average_4 * (1.0 - DETECTION_RATE);
			Serial.print("Calibration done to sensor 4: ");
			Serial.print(calibrated_average_4);
			Serial.println(" cm");
			break;
			
		default:
			break;
	}
}

void calibrate_all_sensors()
{
	uint8_t i;
	for (i = 1; i <= 4; i++)
	{
		calibrate_ultrasound_sensor(i);
	}
}

uint8_t get_echo_pin(uint8_t sensor_number)
{
	switch(sensor_number)
	{
		case SENSOR1:
			return ECHOPIN_SENSOR1;
			break;
			
		case SENSOR2:
			return ECHOPIN_SENSOR2;
			break;
			
		case SENSOR3:
			return ECHOPIN_SENSOR3;
			break;
		
		case SENSOR4:
			return ECHOPIN_SENSOR4;
			break;
		default:
			Serial.println("<ERROR> Invalid sensor number.\n");
			break;
	}
}

uint8_t get_trigger_pin(uint8_t sensor_number)
{
	switch(sensor_number)
	{
		case SENSOR1:
			return TRIGPIN_SENSOR1;
			break;
			
		case SENSOR2:
			return TRIGPIN_SENSOR2;
			break;
			
		case SENSOR3:
			return TRIGPIN_SENSOR3;
			break;
		
		case SENSOR4:
			return TRIGPIN_SENSOR4;
			break;
		default:
			Serial.println("<ERROR> Invalid sensor number.\n");
			break;
	}
}
	
int16_t get_distance(uint8_t sensor_number)
{
	if (sensor_number == 0 || sensor_number > SENSOR4)
	{
		Serial.println("<ERROR> Can't get distance: Invalid sensor number.\n");
		return -1;
	}
	
	uint16_t distance_tmp = 0;
	
	digitalWrite(get_trigger_pin(sensor_number), LOW); // Set the trigger pin to low for 2uS
	delayMicroseconds(2);
	digitalWrite(get_trigger_pin(sensor_number), HIGH); // Send a 10uS high to trigger ranging
	delayMicroseconds(10);
	digitalWrite(get_trigger_pin(sensor_number), LOW); // Send pin low again
	distance_tmp = pulseIn(get_echo_pin(sensor_number), HIGH, 26000); // Read in times pulse
	if (distance_tmp > 0)
	{
		distance[sensor_number - 1] = distance_tmp;
	}
	distance[sensor_number - 1] /= 58;
	delay(50);// Wait 50mS before next ranging
	return distance[sensor_number - 1];
}







