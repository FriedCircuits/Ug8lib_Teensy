//William Garrido
//FriedCircuits
//07-09-2014
//This is what is needed to use the UG8Lib with the Teensy. Include the com files inside the UG8Lib library folder.

#include <SPI.h>
#include <u8g_teensy.h>
//Sets up instance and links to Teensy COM files. 
U8GLIB display(&u8g_dev_ssd1306_128x64_2x_hw_spi, u8g_com_hw_spi_fn);




void setup(){

	display.setFont(u8g_font_6x12);
    display.setColorIndex(1);

	//Not sure if needed but works.
	// SPI backup (avoids conflict between u8g and other SPI libs)
	display.setHardwareBackup(u8g_backup_avr_spi);

}


void loop(){

	display.firstPage();
	  do {
	   display.drawStr( 2, 10, "UGBLIB Teensy");
	   display.drawStr( 5, 20, "FriedCircuits.us");
	  }while( display.nextPage());
	  delay(1000);
}