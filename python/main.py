import serial, time
import get_image

ser = serial.Serial(
    port='COM14',\
    baudrate=115200,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

line = ""
fi = 0
se = 0
while True:
    
    line = ser.readline()
    line = str(line)
    line = line.replace("\\r", "").replace("\\n", "")[2:-1]
    if line != b'':
        print(line)
    if line == '5':
        get_image.get_im()
        hash1=get_image.CalcImageHash("RE/im.jpg")
        hash2=get_image.CalcImageHash("RE/imsc.jpg")
        if get_image.CompareHash(hash1, hash2)>5:
            ser.write('13\n'.encode())
        else:
            ser.write('12\n'.encode())
        fi = 1
    if line == "6":
        hash1=get_image.CalcImageHash("UF/im.jpg")
        hash2=get_image.CalcImageHash("UF/im.jpg")
        if get_image.CompareHash(hash1, hash2)>6:
            ser.write('13\n'.encode())
        else:
            ser.write('12\n'.encode())
        fi = 1
        ser.write('12\n'.encode())
        se = 1
    #if fi == 1 and se == 1:
        #break
    ser.write('0\n'.encode())

ser.close()