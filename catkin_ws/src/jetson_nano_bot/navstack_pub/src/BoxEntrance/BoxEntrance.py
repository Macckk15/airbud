import cv2 
import numpy as np 
import math 
from djitellopy import Tello
import qr_funcs



tello = Tello()
tello.connect()
tello.streamon()

while(1):

    frame1 = tello.get_frame_read().frame

    threshold = 0.2 
    maxWidth = 1100; maxHeight = 850 
    imgHeight, imgWidth = frame1.shape[:2] 
    hScale = 1; wScale = 1 
    thickness = 1 

    if imgHeight > maxHeight: 
        hScale = imgHeight / maxHeight 
        thickness = 6 

    if imgWidth > maxWidth: 
        wScale = imgWidth / maxWidth 
        thickness = 6 

    detectEntrance(frame1)
