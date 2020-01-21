#include "DFPlayer.h"

DFPlayer::DFPlayer(byte rxPin, byte txPin) 
	: serial(rxPin, txPin)
{
	serial.begin(9600);
}

void DFPlayer::initialize()
{
  _sendCommand(0x3F, 0x00, 0x00);
  // Wait until initialization parameters are received (10 bytes)
  while(serial.available() < 10)
  {
    delay(30);
  }
}

void DFPlayer::_sendCommand(byte cmd, byte par1, byte par2)
{
	word checksum = 
		-(VERSION_BYTE
		+ COMMAND_LENGTH
		+ cmd
		+ ACKNOWLEDGE
		+ par1
		+ par2);
		
	byte cmdLine[10] = 
	{
		START_BYTE,
		VERSION_BYTE,
		COMMAND_LENGTH,
		cmd,
		ACKNOWLEDGE,
		par1,
		par2,
		highByte(checksum),
		lowByte(checksum),
		END_BYTE
	};
	
	for(byte k=0; k<10; k++)
	{
		serial.write(cmdLine[k]);
	}
		
}

void DFPlayer::next()
{
	_sendCommand(0x01, 0x00, 0x00);
}

void DFPlayer::previous()
{
	_sendCommand(0x02, 0x00, 0x00);
}

void DFPlayer::track(byte high, byte low)
{
	_sendCommand(0x03, high, low);
}

void DFPlayer::volumeUp()
{
	_sendCommand(0x04, 0x00, 0x00);
}

void DFPlayer::volumeDown()
{
	_sendCommand(0x05, 0x00, 0x00);
}

void DFPlayer::volumeSet(byte volume)
{
	_sendCommand(0x06, 0x00, volume);
}

void DFPlayer::equalizer(EQ band)
{
	_sendCommand(0x07, 0x00, (byte)band);
}

void DFPlayer::repeatTrack(byte high, byte low)
{
	_sendCommand(0x08, high, low);
}

void DFPlayer::reset()
{
	_sendCommand(0x0C, 0x00, 0x00);
}

void DFPlayer::play()
{
	_sendCommand(0x0D, 0x00, 0x00);
}

void DFPlayer::pause()
{
	_sendCommand(0x0E, 0x00, 0x00);
}

void DFPlayer::playFolderFile(byte folder, byte file)
{
	_sendCommand(0x0F, folder, file);
}

void DFPlayer::repeatAll()
{
	_sendCommand(0x11, 0x00, 0x00);
}

void DFPlayer::playFileIndex(byte high, byte low)
{
	_sendCommand(0x12, high, low);
}

void DFPlayer::stop()
{
	_sendCommand(0x16, 0x00, 0x00);
}

void DFPlayer::repeatFolder(byte folder)
{
	_sendCommand(0x17, 0x00, folder);
}

void DFPlayer::random()
{
	_sendCommand(0x18, 0x00, 0x00);
}

void DFPlayer::repeatCurrent()
{
	_sendCommand(0x19, 0x00, 0x00);
}

void DFPlayer::pause(byte mode)
{
	_sendCommand(0x1A, 0x00, mode);
}
