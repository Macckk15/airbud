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

while True:
    # Our operations on the frame come here

    contrast = cv2.convertScaleAbs(img, 15, 1)

    cv2.imshow('Frame', contrast)
    cv2.waitKey(1)

    pt1, pt2, pt3, pt4, bound, rect_w, rect_h = qr_funcs.paperBoundRobot(img)

    if (bound != err_bound):
        qr_funcs.findCorners(pt1, pt2, pt3, pt4, bound, img, rect_w, rect_h)

    else: print('No Bound!')
    
# When everything done, release the capture
left_camera.stop()
left_camera.release()
cv2.destroyAllWindows()