import numpy as np
import cv2
from start_cameras import Start_Cameras
import qr_funcs
import time

path = '../images/image_01.png'
img = cv2.imread(path)

# may need a way to tell if camera not opened
err_bound =[[0, 0], 
            [0, 0]]

# Our operations on the frame come here

blur = cv2.GaussianBlur(img,(15,15),0)

cv2.imshow('Frame', img)
cv2.waitKey(1)

detected, entrance = qr_funcs.detectEntrance(blur)

if (detected):
    cv2.imshow("Detected Lines (in green) - Probabilistic Line Transform", entrance) 
    cv2.waitKey(0) 

# When everything done, release the capture
#left_camera.stop()
#left_camera.release()
#cv2.destroyAllWindows()