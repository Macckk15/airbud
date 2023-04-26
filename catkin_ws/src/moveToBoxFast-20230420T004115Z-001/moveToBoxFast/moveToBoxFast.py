
import torch
import cv2
import numpy as np
import qr_funcs as qr
from djitellopy import Tello
import time

import math

def rotate(func):
    func(8)

def getMean(roi):
    mean = cv2.mean(roi)

    roi_mean = (mean[0] + mean[1] + mean[2])/3

    return roi_mean

def getHue(roi):
    roi_hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
    mean = cv2.mean(roi_hsv)
    mean_h = mean[0]
    mean_s = mean[1]
    mean_v = mean[2]

    return int(mean_h), int(mean_s), int(mean_v)

min_hue_diff = 100
min_val_diff = 100

box_hue = 17
box_sat = 120
box_val = 40

val_min = 20

val_tol = 10
sat_tol = 40
hue_tol = 7

empty_scans = 0
failures = 0
dir_changes = 0

codes = [None, None, None, None, None, None, None]
box_coords = [(None, None), (None, None), (None, None), (None, None), (None, None), (None, None)]

# POTENTIAL APPROACH IDEA (NO CONTINUOUS UPDATES)
#   Locate a boc
#   Move a LARGE distance towards it
#   Start scanning for qr code/panning
#   Will need to move a distance in proportion to bounding box size

# Need positional tracking
# May want to call a function whenever changing attitude (yaw spec.), that keeps track
# of current pos. 

# Need to find a way to stick with going to a specific box
    # Avoid false positives better
    # Identify individual boxes
        # Orientations won't be the same - average value inside bbox?

degree_ratios = [1, 2, 1]
mean_tol = 10

yolo_path = r'C:\Users\turki\Desktop\yolo_top\yolov5-7.0'
weight_path = r'C:\Users\turki\Desktop\yolo_top\yolov5-7.0\runs\train\exp8\weights\best.pt'

model = torch.hub.load(yolo_path, 'custom', path=weight_path, source='local')

tello = Tello()
tello.connect()
tello.takeoff()
time.sleep(1)
tello.move_up(40)
tello.streamon()

model.conf = 0.5

rotations = [tello.rotate_clockwise, tello.rotate_counter_clockwise]

units_to_move = 0

#units_to_move = box_area/230

# 95", 241.3cm, 47177, 245

# 86", 55660, 240

rotate_count = 0
dir = bool(0)

x = 0
y = 0

attempts = 0

# QR CODE APPROACH:
# In current state, box detection detects the qr code on top of the box itself
# This may be used to give an image of the paper that can be used to get the paper bound, and ultimately
# Scan the QR code.

# Considerations:
#   Current second-mode implementation for thresholding may not work as well on just the box.
#   However, the general approach should work since there are really only 2 colors present: Brown and white
#   The QR code may also not be detected as a box. This approach may not work consistently enough
#   We only want to scan a qr code if it is around the middle/bottom of the screen. 
#   Otherwise, the angle will likely be too shallow to perform a perspective transformation
#   That doesn't lose a ton of detail.

# Look at detected boxes.
# Find target box, but also save any boxes that are below the midpoint
# If below the midpoint, check average value inside this box. 
# If value satisfies the target threshold, feed nto paperbound and findcorners.
# If a QR code is not detected (no effect from the prev condition outcome),
# Feed bottom half of the image into paperbound. Consider cropping sides too.

# POSITIONAL TRACKING
# Drone and robot start at same orientation.
# X axis is the direction robot and drone are facing at comp start
# Y axis is perpendicular

theta = 0
x_pos = 0
y_pos = 0

box_count_target = 7
box_count = 0

while(box_count != 7):

    target = None
    image = tello.get_frame_read().frame
    clean = image
    results = model(image)
    labels, cord_thres = results.xyxyn[0][:, -1].numpy(), results.xyxyn[0][:, :-1].numpy()

    if (len(cord_thres) > 0):

        # At least 1 box found
        counter = 0

        num_boxes = len(cord_thres)

        boxes = [4] * num_boxes

        boxes=[]
        rows, cols= num_boxes, 4
        for i in range(rows):
            col = []
            for j in range(cols):
                col.append(0)
            boxes.append(col)

        height, width = image.shape[:2]

        for i in range(0, num_boxes):

            boxes[i][0] = cord_thres[i][0]
            boxes[i][1] = cord_thres[i][1]
            boxes[i][2] = cord_thres[i][2]
            boxes[i][3] = cord_thres[i][3]
            
        maxWidth = 1100; maxHeight = 850

        if height > maxHeight:
            hScale = height / maxHeight
            thickness = 6
        if width > maxWidth:
            wScale = width / maxWidth
            thickness = 6

        hScale = 1
        wScale = 1

        if hScale > wScale:
            image = cv2.resize(image, (int(width / hScale), maxHeight))
        elif hScale < wScale:
            image = cv2.resize(image, (maxWidth, int(height / wScale)))

        height, width = image.shape[:2]
        frame_res = height * width

        # Initialize navigation goal
        if (boxes[0][0] != 0) and (boxes[0][1] != 0): # Boxes found in new frame
            
            bound_width = int(width * abs(boxes[0][0] - boxes[0][2]))
            bound_height = int(height * abs(boxes[0][1] - boxes[0][3]))
            bound_area = bound_width * bound_height

            tl = (int(width * boxes[0][0]), int(height * boxes[0][1]))
            br = (int(width * boxes[0][2]), int(height * boxes[0][3]))

            # Save an image of this frame cropped to the ROI
            # Will be used to calculate average value (used as an identifier)

            roi = image[tl[1]:tl[1] + bound_height, tl[0]:tl[0] + bound_width]
            hue, sat, val = getHue(roi)
            #19, 141

            cv2.rectangle(image, tl, br, (0, 255, 0), 2)
            cv2.putText(image, 'H: {} S: {}  V: {} '.format(hue, sat, val), (tl[0], tl[1]-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,0,0), 2)

            if (box_hue - hue_tol < hue < box_hue + hue_tol):
                if (bound_area < 110000) and (val > val_min):
                #if (box_sat - sat_tol < sat < box_sat + sat_tol):
                    target = boxes[0]
                    print("HUE: {}".format(hue))
                    print("VALUE: {}".format(val))
                    target_hue = hue
                    target_val = val
                    empty_scans = 0
                    failures = 0
                    rotate_count = 0 
                    dir = 0
                    dir_changes = 0

            else:

                for i in range(1, num_boxes):

                    bound_width = int(width * abs(boxes[i][0] - boxes[i][2]))
                    bound_height = int(height * abs(boxes[i][1] - boxes[i][3]))

                    bound_area = bound_width * bound_height

                    tl = (int(width * boxes[i][0]), int(height * boxes[i][1]))
                    br = (int(width * boxes[i][2]), int(height * boxes[i][3]))

                    # Save an image of this frame cropped to the ROI
                    # Will be used to calculate average value (used as an identifier)

                    roi = image[tl[1]:(tl[1] + bound_height), tl[0]:(tl[0] + bound_width)]
                    hue, sat, val = getHue(roi)

                    cv2.rectangle(image, tl, br, (0, 255, 0), 2)
                    cv2.putText(image, 'H: {} S: {} V: {} '.format(hue, sat, val), (tl[0], tl[1]-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,255,255), 2)
                    
                    if (box_hue - hue_tol < hue < box_hue + hue_tol):
                        if (bound_area < 110000) and (val > val_min):
                            #if (box_sat - sat_tol < sat < box_sat + sat_tol):
                            target = boxes[i]
                            print("HUE: {}".format(hue))
                            print("VALUE: {}".format(val))
                            target_hue = hue
                            target_val = val
                            empty_scans = 0
                            failures = 0
                            rotate_count = 0 
                            dir = 0
                            dir_changes = 0
                            break

            if target is not None:

                bound_width = int(width * abs(target[0] - target[2]))
                bound_height = int(height * abs(target[1] - target[3]))

                tl = width * target[0]
                tr = width * target[2]

                top_left = (int(width * target[0]), int(height * target[1]))
                bottom_right = (int(width * target[2]), int(height * target[3]))

                cv2.rectangle(image, top_left, bottom_right, (0, 255, 255), 2)
                cv2.putText(image, 'H: {} S: {} V: {} '.format(hue, sat, val), (top_left[0], top_left[1]-10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,255,255), 2)
                cv2.putText(image, 'AREA: {} '.format(bound_area), (bottom_right[0], bottom_right[1]-10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,0,255), 2)

                bound_area = bound_width * bound_height

                if (tl > (width // 2)) and (tr > (width // 2)):
                    # Both sides of the box are to the right of the frame's midpoint. yaw right
                    rot_mult = (tr - (width // 2)) / (width // 2) # Gives decimal representing how far in the right side of the median the top left corner is
                    # Acts as multiplier for how much to rotate. Max is 25
                    tello.rotate_clockwise(int(rot_mult * 30))
                    theta = theta - (int(rot_mult * 30))
                    if (theta < 0):
                        theta = 360 + theta
                    else:
                        theta = theta % 360
                    print('yaw right')                

                if (tl < (width // 2)) and (tr < (width // 2)):
                    rot_mult = ((width // 2) - tl) / (width // 2)
                    # Both sides of the box are to the left of the frame's midpoint. yaw left
                    tello.rotate_counter_clockwise(int(rot_mult * 30))
                    theta = theta + (int(rot_mult * 30))
                    if (theta < 0):
                        theta = 360 + theta
                    else:
                        theta = theta % 360
                    print('yaw left')

                units_to_move = int((100000 / bound_area) * 130)

                #print('AREA: {}'.format(bound_area))

                cv2.imwrite(r"C:\Users\turki\Desktop\navgoals\goal" + str(x) + ".png",image)

                while (units_to_move > 500):

                    tello.move_forward(500)
                    x += 500 * math.cos(math.radians(theta))
                    y += 500 * math.sin(math.radians(theta))
                    units_to_move -= 500

                if (units_to_move < 20):

                    tello.move_forward(20)
                    x += 20 * math.cos(math.radians(theta))
                    y += 20 * math.sin(math.radians(theta))
                    units_to_move = 0

                else:

                    tello.move_forward(units_to_move)
                    x += units_to_move * math.cos(math.radians(theta))
                    y += units_to_move * math.sin(math.radians(theta))
                    units_to_move = 0

                #QR CODE SCANNING/MOVEMENT
                tello.move_down(35)

                # take photo to scan qr code
                # Look at bounding boxes for QR code
        
                orientation_attempts = 0
                orientations = 0
                code = 'Z'

                while (orientations < 3):

                    cropped = clean[height//2:height, (width // 5): 4 * (width // 5)]

                    while (attempts < 3):

                        if (cropped is not None):
                          
                            #print('Height {}'.format(height))
                            #print('Width {}'.format(width))
                            pt1, pt2, pt3, pt4, bound, rect_w, rect_h = qr.paperBound(cropped)
                            cv2.imwrite(r"C:\Users\turki\Desktop\navgoals\crop" + str(box_count) + ".png",cropped)
                            if (rect_h is not None) and (rect_w is not None):
                                code = qr.findCorners(pt1, pt2, pt3, pt4, bound, cropped, rect_w, rect_h)
                
                        if (code is not None):
                            break
                        else:
                            attempts += 1

                    if (code is not None):
                        break

                    else:
                        theta_temp = theta - 90
                        if (theta_temp < 0):
                            theta_temp += 360
                        else:
                            theta_temp = theta_temp % 360

                        tello.move_right(20)

                        x += 20 * math.cos(math.radians(theta_temp))
                        y += 20 * math.sin(math.radians(theta_temp))

                        tello.rotate_counter_clockwise(20)
                        theta = theta + 20

                        if (theta < 0):
                            theta = 360 + theta
                        else:
                            theta = theta % 360

                        orientations += 1
                        results = model(clean)
                        labels, cord_thres = results.xyxyn[0][:, -1].numpy(), results.xyxyn[0][:, :-1].numpy()

                codes[box_count] = code
                box_coords[box_count] = x, y

                print("X: {}, Y: {}".format(x, y))

                box_count += 1
                if (box_count == 7):
                    print('Box found')
                    break

            else:
             # Target is None
                empty_scans += 1
                cv2.imshow("out", image)
                cv2.waitKey(1)

                if (empty_scans == 8):

                    empty_scans += 1
                    failures += 1
                    tello.rotate_counter_clockwise(10)

                    theta = theta + 30
                    if (theta < 0):
                        theta = 360 + theta
                    else:
                        theta = theta % 360

                    if (failures == 12):
                        failures = 0
                        tello.move_forward(30)
                        x += 30 * math.cos(math.radians(theta))
                        y += 30 * math.sin(math.radians(theta))

                    print("FAILURES: {}".format(failures))
    cv2.imshow("out", image)
    cv2.waitKey(1)

print('Coords found!')
