import smbus
import time

# for speech
from espeak import espeak

# the commands from the Arduino
GETMUSICSWITCH  = 0
GETSPEECHSWITCH = 1

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

    # write 'command' to Arduino
    writeNumber(GETSPEECHSWITCH)

#    print "RPI: Hi Arduino, I sent you ", var

    # sleep one second
    time.sleep(1)

    # read answer / value from Arduino
    number = readNumber()

#    var = input("Enter 1 - 9: ")
#    if not var:
#        continue


#    print "Arduino: Hey RPI, I received a digit ", number
#    print

    if number == 1:
		espeak.synth("Hello Campuseros.")

    if number == 2:
		espeak.synth("This is fucking awesome.")
