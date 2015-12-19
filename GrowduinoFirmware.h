#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <avr/pgmspace.h>
#include <avr/wdt.h>

//#define WATCHDOG 1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <Time.h>


#define DHT22_NO_FLOAT 1

#define MINVALUE -999

#define GET 1
#define POST 2

// light sensor on analog A8
#define LIGHT_SENSOR_PIN_1 8
#define LIGHT_SENSOR_PIN_2 9
#define LIGHT_SENSOR_PIN_UPS 10

#define USE_PH_SENSOR 1
#ifdef USE_PH_SENSOR
// calibrate this. Will be saved to config file, so it can be adjusted
#define PH_4 40
#define PH_7 200
#endif
#define PH_DATA 11


#define USE_EC_SENSOR 1
#ifdef USE_EC_SENSOR
// calibrate this. Will be saved to config file, so it can be adjusted
#define EC_LOW_ION 500
#define EC_HIGH_ION 200
#endif
#define EC_ENABLE 27
#define EC_DATA 28
#define EC_SAMPLE_TIMES 5


#define USE_CO2_SENSOR 1

#ifdef USE_CO2_SENSOR
// calibrate this. Will be saved to config file, so it can be adjusted. 
#define CO2_400 4.535  //not an integer
#define CO2_40k 3.206  //not an integer
#endif
#define CO2_DATA 12

#define DHT22_PIN 22
#define ONEWIRE_PIN 23
#define ONEWIRE_PIN2 24
#define USOUND_TRG 25
#define USOUND_ECHO 26


#define RELAY_START 34


#define BUFSIZE 256

#define ALARM_STR_MAXSIZE 32

// TRIGGERS - ALERTS must be 31 or lower, or random crashes occur. Really.
#define TRIGGERS 42
#define ALERTS 12


#define ANALOG_READ_AVG_TIMES 3
#define ANALOG_READ_AVG_DELAY 10


#define ALERT_MSG_LEN 64
#define ALERT_TARGET_LEN 32

#define OUTPUTS 12

#define LOGGERS 10

#define DEBUG 1

#define LCD_BUFFER_LINES 9

#define DISPLAY_2004 1

#ifdef DISPLAY_2004
#define LCD_DISPLAY_LINES 4
#define LCD_DISPLAY_LEN 20

#else
#define LCD_DISPLAY_LINES 2
#define LCD_DISPLAY_LEN 16
#endif


#define MEGA 1

#ifdef DEBUG
#define DEBUG_OUTPUT 1
#define DEBUG_SDCARD 1
#define DEBUG_RB_DATA 1
#define DEBUG_TRIGGERS 1
#define DEBUG_ALERTS 1
#define DEBUG_HTTP 1
#define DEBUG_SMTP 1
//#define DEBUG_LCD 1
#define DEBUG_CALIB 1
#endif

// How many output chages do we keep in memory
#define LOGSIZE 25

// #include "config.h"
#include "Logger.h"
#include "RingBuffer.h"
#include "daytime.h"
#include "sdcard.h"
#include "config.h"
#include "outputs.h"
#include "trigger.h"
#include "ultrasound.h"
#include "ds.h"
#include "Lcd.h"
#include "alerts.h"
#include "smtp.h"

#ifdef USE_PH_SENSOR
#include "phmeter.h"
#endif

#ifdef USE_EC_SENSOR
#include "ec.h"
#endif

#ifdef USE_CO2_SENSOR
#include "co2.h"
#endif

extern int ether;
void pFreeRam();
extern File sd_file;
int analogReadAvg(int pin);

#define NONE -1
#define STATE_ON 1
#define STATE_OFF 0
#define STATE_ON_ALWAYS 2
