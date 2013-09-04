import smbus		# for I2C
import time		# for delay
#import subprocess	# for using mplayer in the background
import pygame


# for speech
from espeak import espeak

# the commands from the Arduino
GETMUSICSWITCH  = 0
GETSPEECHSWITCH = 1

# the music states, also defined in Arduino
MUSICSTOPPED = 0;
MUSICPLAYING = 1;
MUSICPAUSED  = 2;

# stores the last played title / wave file
lastFile = 0;

# init pygame
pygame.mixer.init()

# this stores the laste values to not repeat the last command again and again
lastMusicValue  = 0
lastSpeechValue = 0

# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04

def writeNumber(value):
    bus.write_byte(address, value)
    # bus.write_byte_data(address, 0, value)
    return -1

def readNumber():
    number = bus.read_byte(address)
    # number = bus.read_byte_data(address, 1)
    return number


# main loop
while True:

    #--------
    # SPEECH
    #--------
    # write 'command' to Arduino
    writeNumber(GETSPEECHSWITCH)
    time.sleep(0.5)

    # read answer / value from Arduino
    number = readNumber()

    if number != lastSpeechValue:

	# store value
	lastSpeechValue = number
        
	if number == 1:
		espeak.synth("Hello Campuseros.")
		# sleep some time
    		time.sleep(2)

        if number == 2:
		espeak.synth("This is fucking awesome.")
		# sleep some time
    		time.sleep(2)


    #--------
    # MUSIC
    #--------
    # write 'command' to Arduino
    writeNumber(GETMUSICSWITCH)
    time.sleep(0.5)

    # read answer / value from Arduino
    number = readNumber()

    if number != lastMusicValue:

	# store value
	lastMusicValue = number
        
	if number == MUSICSTOPPED:
		# stop music
		pygame.mixer.music.stop()

        if number == MUSICPLAYING:
		if lastFile == 0:
			pygame.mixer.music.load("/home/pi/SilenceIkillYou.wav")
			pygame.mixer.music.play()
		if lastFile == 1:
			pygame.mixer.music.load("/home/pi/AreYouScared.wav")
			pygame.mixer.music.play()

		lastFile = lastFile + 1

		if lastFile == 2:
			lastFile = 0

        if number == MUSICPAUSED:
		# play music
		pygame.mixer.music.pause()
