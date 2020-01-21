#ifndef DFPLAYER_H
#define DFPLAYER_H

#include "SoftwareSerial.h"
#include <Arduino.h>


enum CMD_PARAMS
{
	START_BYTE = 0x7E,
	VERSION_BYTE = 0xFF,
	COMMAND_LENGTH = 0x06,
	END_BYTE = 0xEF,
	ACKNOWLEDGE = 0x00
};

enum class EQ
{
	NORMAL,
	POP,
	ROCK,
	JAZZ,
	CLASSIC,
	BASE
};

class DFPlayer{
public:
	DFPlayer(byte, byte);
  void initialize();
	void next();
	void previous();
	void track(byte, byte);
	void volumeUp();
	void volumeDown();
	void volumeSet(byte);
	void equalizer(EQ);
	void repeatTrack(byte, byte);
	void reset();
	void play();
	void pause();
	void playFolderFile(byte, byte);
	void repeatAll();
	void playFileIndex(byte, byte);
	void stop();
	void repeatFolder(byte);
	void random();
	void repeatCurrent();
	void pause(byte);
	SoftwareSerial serial;
	
private:
	void _sendCommand(byte, byte, byte);
};

#endif
