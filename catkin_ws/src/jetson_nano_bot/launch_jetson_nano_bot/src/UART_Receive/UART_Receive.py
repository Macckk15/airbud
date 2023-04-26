import serial

x_accel = ""
y_accel = ""
z_accel = ""

x_gyro = ""
y_gyro = ""
z_gyro = ""

#/dev/ttyACM0
# may need to be changed for arduino mega

                                            # Set up UART connection
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=2, xonxoff=False, rtscts=False, dsrdtr=False) 
ser.flushInput()
ser.flushOutput()
while True:
  data_raw = ser.readline()                 # Receive incoming csvs
  #data_raw = data_raw.decode()             # Convert from byte format to str
  data_count = 0                            # Initialize received value counter

                                            # State machine for building measurements as string

  print(data_raw)

  if (counter > 3):
    XAMagPos = data_raw.find("A")
    YAMagPos = data_raw.find("B")
    ZAMagPos = data_raw.find("C")
    XGMagPos = data_raw.find("D")
    YGMagPos = data_raw.find("E")
    ZGMagPos = data_raw.find("F")
    EndPos = data_raw.find("G")
    XMagPos = data_raw.find("H")
    YMagPos = data_raw.find("I")
    ZMagPos = data_raw.find("J")
    XAMag = float(data_raw[XAMagPos+2:YAMagPos])
    YAMag = float(data_raw[YAMagPos+2:ZAMagPos])
    ZAMag = float(data_raw[ZAMagPos+2:XGMagPos])
    XGMag = float(data_raw[XGMagPos+2:YGMagPos])
    YGMag = float(data_raw[YGMagPos+2:ZGMagPos])
    ZGMag = float(data_raw[ZGMagPos+2:EndPos])
    msg.header.stamp = rospy.get_rostime()
    msg.accel.linear.x = XMag
    msg.magnetic_field.y = YMag
    msg.magnetic_field.z = ZMag
    print(XMag)
    pub.publish(msg)
counter = counter + 1

  print('X acceleration: {}'.format(x_accel))
  print('Y acceleration: {}'.format(y_accel))
  print('Z acceleration: {}'.format(z_accel))
  print('X gyro: {}'.format(x_gyro))
  print('Y gyro: {}'.format(y_gyro))
  print('Z gyro: {}'.format(z_gyro))

