#include <atmel_start.h>
#include <stdio.h>

#define SEND_ALIVE_SIGNAL 150000
#define BUTTON_DEBOUNCE_TRESHOLD 500

#define BUTTON1_LED_ON_EVENT_CHAR  'o'
#define BUTTON1_LED_OFF_EVENT_CHAR 'f'

const char *const device_name = "RemoteSwitch";
const char *const fw_version = "FW: 1.0.0";
const char *const hw_verison = "HW: 1.0";
const char *const company_name = "kelectronics.pl";
const char *const build_date = __DATE__;
const char *const build_time = __TIME__;
 
const char *const button1_event_char =  "a";
const char *const button2_event_char =  "b";
const char *const alive =               "!";


static int print(char * str);

int main(void)
{
	uint32_t alive_counter = 0;
	uint32_t button1_debounce_counter = 0;
	uint32_t button2_debounce_counter = 0;
	bool button1_detected_frame_send = false;
	bool button2_detected_frame_send = false;

	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	USART_0_enable();

	BUTTON1_LED_set_level(false);

	print((char*)device_name);
	print((char*)fw_version);
	print((char*)hw_verison);
	print((char*)build_date);
	print((char*)build_time);

	/* Replace with your application code */
	while (1)
	{
	/* Heartbeat  */
		alive_counter++;
		if(alive_counter == SEND_ALIVE_SIGNAL)
		{
			print((char*)alive);
			alive_counter=0;
		}

	/* Button 1 detection */
		if(BUTTON1_get_level())
		{
			/* button detected */
			button1_debounce_counter++;
		}
		else
		{
			/* reset button debounce time */
			button1_debounce_counter = 0;
			button1_detected_frame_send=false;
		}

		if(button1_debounce_counter > BUTTON_DEBOUNCE_TRESHOLD)
		{
			/* send coin detection signal */
			if(button1_detected_frame_send == false)
			{
				print((char*)button1_event_char);
				button1_detected_frame_send = true;
			}
		}

	/* Button 2 detection */
		if(BUTTON2_get_level())
		{
			/* button detected */
			button2_debounce_counter++;
		}
		else
		{
			/* reset button debounce time */
			button2_debounce_counter = 0;
			button2_detected_frame_send=false;
		}

		if(button2_debounce_counter > BUTTON_DEBOUNCE_TRESHOLD)
		{
			/* send coin detection signal */
			if(button2_detected_frame_send == false)
			{
				print((char*)button2_event_char);
				button2_detected_frame_send = true;
			}
		}
	
	/* Button 1 LED driver */
		if(USART_0_is_rx_ready())
		{
			switch((char)USART_0_get_data())
			{
				case BUTTON1_LED_ON_EVENT_CHAR:
					BUTTON1_LED_set_level(true);
					break;

				case BUTTON1_LED_OFF_EVENT_CHAR:
					BUTTON1_LED_set_level(false);
					break; 

				default: 
				/* Do nothing */
					break;
			}
		}
	}
}

static int print(char * str)
{
	uint8_t counter = 0;
	while(str[counter])
	{
		USART_0_write(str[counter]);
		counter++;
	}
	USART_0_write('\r');
	USART_0_write('\n');
	return counter;
}
