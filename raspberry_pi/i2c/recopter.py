import smbus
import time

# for speech
from espeak import espeak

# the commands from the Arduino
GETMUSICSWITCH  = 0
GETSPEECHSWITCH = 1

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
    time.sleep(1)

    # read answer / value from Arduino
    number = readNumber()


#    var = input("Enter 1 - 9: ")
#    if not var:
#        continue


#    print "Arduino: Hey RPI, I received a digit ", number
#    print

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
