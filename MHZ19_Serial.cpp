/*
  MHZ19_Serial.cpp - MH-Z19 CO2 sensor library for ESP-WROOM-02(esp8266) or Arduino
  version 0.2
  
  
*/

#include "SoftwareSerial.h"
#include "MHZ19_Serial.h"


// public

MHZ19_Serial::MHZ19_Serial(){
}

MHZ19_Serial::MHZ19_Serial(int rx, int tx){
	begin(rx,tx);
}

MHZ19_Serial::~MHZ19_Serial(){
}

void MHZ19_Serial::begin(int rx, int tx){
	setRX(rx);
	setTX(tx);
}

void MHZ19_Serial::setAutoCalibration(bool autocalib){
	writeCommand( autocalib ? autocalib_on : autocalib_off );
}

void MHZ19_Serial::calibrateZero() {
	writeCommand( zerocalib );
}

void MHZ19_Serial::calibrateSpan(int ppm) {
	if( ppm < 1000 )	return;

	uint8_t com[MHZ19_Serial::REQUEST_CNT];
	for(int i=0; i<MHZ19_Serial::REQUEST_CNT; i++) {
		com[i] = spancalib[i];
	}
	com[3] = (uint8_t)(ppm/256);
	com[4] = (uint8_t)(ppm%256);
	writeCommand( zerocalib );
}

int MHZ19_Serial::getPPM() {
	return getSerialData(PPM);
}

int MHZ19_Serial::getTemperature() {
	return getSerialData(TEMPERATURE);
}

int MHZ19_Serial::getStatus() {
	return getSerialData(STAT);
}

bool MHZ19_Serial::isWarming(){
	return (getStatus() <=1);
}

//protected
void MHZ19_Serial::writeCommand(uint8_t cmd[]) {
	writeCommand(cmd,NULL);
}

void MHZ19_Serial::writeCommand(uint8_t cmd[], uint8_t response[] = NULL) {
	SoftwareSerial co2serial = SoftwareSerial( rx_pin, tx_pin );
	co2serial.begin(9600);
	uint8_t checksum = mhz19_checksum(cmd);
	for (int i = 0; i < REQUEST_CNT; i++) {
	    co2serial.write(cmd[i]);
	}
	co2serial.write(checksum);
	co2serial.flush();
	
	if (response != NULL) {
		co2serial.readBytes(response, MHZ19_Serial::RESPONSE_CNT);
	}
}


//private

int MHZ19_Serial::getSerialData(MHZ19_DATA flg) {
	uint8_t buf[MHZ19_Serial::RESPONSE_CNT];
	writeCommand(getppm, buf);

	int co2 = 0, co2temp = 0, co2status =  0;

	// parse
	if (buf[0] == 0xff && buf[1] == 0x86 && mhz19_checksum(buf) == buf[MHZ19_Serial::RESPONSE_CNT-1]) {
		co2 = buf[2] * 256 + buf[3];
		co2temp = buf[4] - 40;
		co2status =  buf[5];
	} else {
		co2 = co2temp = co2status = -1;
	}

	switch(flg) {
		case MHZ19_DATA::TEMPERATURE:
			return co2temp;
			break;
		case MHZ19_DATA::STAT:
			return co2status;
			break;
		case MHZ19_DATA::PPM:
		default:
			return co2;
			break;
	}
}	

uint8_t MHZ19_Serial::mhz19_checksum( uint8_t com[] ) {
	uint8_t sum = 0x00;
	for ( int i = 1; i < MHZ19_Serial::REQUEST_CNT; i++) {
		sum += com[i];
	}
	sum = 0xff - sum + 0x01;
	return sum;
}

void MHZ19_Serial::setRX(int rx) {
	rx_pin = rx;
}

void MHZ19_Serial::setTX(int tx) {
	tx_pin = tx;
}
