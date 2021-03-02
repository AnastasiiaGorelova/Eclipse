import serial

with serial.Serial('/dev/tty.usbmodem143101') as ser:
    MenuFlag = 0
    while not MenuFlag:
        line = str(ser.readline())
        print(line)
        if "MENU" in line:
            MenuFlag = 1
ser.close()
