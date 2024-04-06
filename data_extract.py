# -*- coding: utf-8 -*-
import time
import serial
SCREEN_DISPLAY=True
SAVE_TO_FILE=True
DELIMITER=','

#SERIAL_PORT='/dev/ttyACM0' # serial port terminal
SERIAL_PORT='COM3'

file_name= 'choice_output2.txt'
fid= open(file_name,'ab')

scale=serial.Serial(SERIAL_PORT,timeout=20,baudrate=57600)

while True:
    str_scale=scale.readline()

    if SCREEN_DISPLAY: print(str.encode(DELIMITER)+str_scale)
    time.sleep(0.01)  # in seconds
    if SAVE_TO_FILE: fid.write(str_scale)

scale.close()
fid.close()

