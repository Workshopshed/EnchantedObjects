# Reference https://github.com/arduino/YunBridge/blob/master/bridge/bridge.py
#           http://pyserial.sourceforge.net/

import serial

try:
   ser = serial.Serial('/dev/ttyATH0', 115200, timeout=60, writeTimeout=60) # Baudrate needs to be mirrored on ATMega side
except:
        exit(1)           # quit as we can't start the serial port

line = ser.readline()   # read a '\n' terminated line

while line != "":
    print(line);            # Display on console
    ser.write(line)         # Echo it back
    line = ser.readline()   # read next line

print("timeout")
ser.close()