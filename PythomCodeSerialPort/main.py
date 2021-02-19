import serial
with serial.Serial('/dev/tty.usbmodem143101') as ser:
    while(True):
        line = ser.readline()
        print(line)