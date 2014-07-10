#include <Arduino.h>
#include "u8glib.h"
#include "SPI.h"
uint8_t u8g_com_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_STOP:
      //STOP THE DEVICE
    break;

    case U8G_COM_MSG_INIT:
		//INIT HARDWARE INTERFACES, TIMERS, GPIOS...
		pinMode(9, OUTPUT);
		//For hardware SPI
		pinMode(SS, OUTPUT);
		SPI.begin();
		SPI.setClockDivider(SPI_CLOCK_DIV2);
		
		
		
	    pinMode(14, OUTPUT);
		digitalWrite(14, HIGH);
	    // VDD (3.3V) goes high at start, lets just chill for a ms
		delay(1);
		// bring reset low
		digitalWrite(14, LOW);
		// wait 10ms
		delay(10);
		// bring out of reset
		digitalWrite(14, HIGH);
		
		//pinMode(MOSI, OUTPUT);
		//pinMode(SCK, OUTPUT);

		/*
		clkport     = portOutputRegister(digitalPinToPort(SCK));
		clkpinmask  = digitalPinToBitMask(SCK);
		mosiport    = portOutputRegister(digitalPinToPort(MOSI));
		mosipinmask = digitalPinToBitMask(NOSI);
		csport      = portOutputRegister(digitalPinToPort(SS));
		cspinmask   = digitalPinToBitMask(SS);
		dcport      = portOutputRegister(digitalPinToPort(9));
		dcpinmask   = digitalPinToBitMask(9);
		*/
		
    break;

    case U8G_COM_MSG_ADDRESS:  
      //SWITCH FROM DATA TO COMMAND MODE (arg_val == 0 for command mode)
	  if (arg_val != 0)
      {
          digitalWrite(9, HIGH);
      }
      else
      {
          digitalWrite(9, LOW);
      }

    break;
	
	case U8G_COM_MSG_CHIP_SELECT:
		if(arg_val == 0)
		{
			digitalWrite(SS, HIGH);
		}
		else{
			digitalWrite(SS, LOW);
		}
	break;

    case U8G_COM_MSG_RESET:
      //TOGGLE THE RESET PIN ON THE DISPLAY BY THE VALUE IN arg_val
	  digitalWrite(14, arg_val);
    break;

    case U8G_COM_MSG_WRITE_BYTE:
      //WRITE BYTE TO DEVICE
	  SPI.transfer(arg_val);

    break;

    case U8G_COM_MSG_WRITE_SEQ:
    case U8G_COM_MSG_WRITE_SEQ_P:
	{
      //WRITE A SEQUENCE OF BYTES TO THE DEVICE
	  register uint8_t *ptr = static_cast<uint8_t *>(arg_ptr);
	  while(arg_val > 0){
		SPI.transfer(*ptr++);
		arg_val--;
	  }
	 }
    break;

  }
  return 1;
}