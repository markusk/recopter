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
	try:
		bus.write_byte(address, value) # 5 = I/O error
	except IOError, err:
#		return self.errMsg()
		return -1
    	# bus.write_byte_data(address, 0, value)
    	return 0


def readNumber():
    number = bus.read_byte(address)
    # number = bus.read_byte_data(address, 1)
    return number


# main loop
while True:

    #-----------------------------------------
    # wait until I2C / Arduino becomes ready
    #-----------------------------------------
    while writeNumber(0) == -1:
	time.sleep(2)

    # we are ready now. read the first result, but ignore it
    number = readNumber()


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
		if lastFile == 2:
			pygame.mixer.music.load("/home/pi/t2_trust_me.wav")
			pygame.mixer.music.play()
		if lastFile == 3:
			pygame.mixer.music.load("/home/pi/t2_hasta_la_vista.wav")
			pygame.mixer.music.play()
		if lastFile == 4:
			pygame.mixer.music.load("/home/pi/t1_be_back.wav")
			pygame.mixer.music.play()
		if lastFile == 5:
			pygame.mixer.music.load("/home/pi/exterminateLoud.wav")
			pygame.mixer.music.play()

		lastFile = lastFile + 1

		if lastFile == 6:
			lastFile = 0

        if number == MUSICPAUSED:
		# play music
		pygame.mixer.music.pause()
