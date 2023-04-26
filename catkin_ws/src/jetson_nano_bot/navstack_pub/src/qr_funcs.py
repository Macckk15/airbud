import cv2
import math
import numpy as np
import pyzbar.pyzbar as pyzbar
from matplotlib import pyplot as plt
from scipy.signal import argrelextrema

def postprocess(gray_qr):

    codes = pyzbar.decode(gray_qr)

    codeData = None
    for code in codes:
        codeData = code.data.decode()
        codeType = code.type
        print('Code scanned: {}'.format(codeData))

    cv2.imshow('QR code', gray_qr)
    cv2.waitKey(1)

    return codeData

def swapCoords(point):
    point = list(point)
    temp = point[0]
    point[0] = point[1]
    point[1] = temp

    return point

def houghIntersection(theta_1, rho_1, theta_2, rho_2):

    error = 0

    if (theta_1 is None) or (rho_1 is None) or (theta_2 is None) or (rho_2 is None):
        print('Error: None parameter passed.')
        x0 = error
        y0 = error
   
    else:

        A = np.array([
                [np.cos(theta_1), np.sin(theta_1)],
                [np.cos(theta_2), np.sin(theta_2)]
            ])

        b = np.array([[rho_1], [rho_2]])

        try:
            x0, y0 = np.linalg.solve(A, b)              #linalg.solve
            x0, y0 = int(np.round(x0)), int(np.round(y0))
        except:
            x0 = error
            y0 = error
            pass

    return x0, y0

def replaceClosestCorner(new_pt, corner1, corner2, corner3, corner4):   # Replaces one corner with a new corner

    pts = [corner1, corner2, corner3, corner4]
    pts = list(pts)
    
    pt_d = [[None, None], [None, None], [None, None], [None, None]]
    pt_d = list(pt_d)

    distance = [None, None, None, None]
    distance = list(distance)

                                                           # Used with new_pt being a hough line intersection (being an accurate paper corner)
                                                           # and replacing the corner nearest to this point in the xy coordinate system

    pt_d[0] = [abs(new_pt[0] - corner1[0]), abs(new_pt[1] - corner1[1])]  
    pt_d[1] = [abs(new_pt[0] - corner2[0]), abs(new_pt[1] - corner2[1])]
    pt_d[2] = [abs(new_pt[0] - corner3[0]), abs(new_pt[1] - corner3[1])]
    pt_d[3] = [abs(new_pt[0] - corner4[0]), abs(new_pt[1] - corner4[1])]

    distance[0] = np.sqrt(np.square(pt_d[0][0]) + np.square(pt_d[0][1]))
    distance[1] = np.sqrt(np.square(pt_d[1][0]) + np.square(pt_d[1][1]))
    distance[2] = np.sqrt(np.square(pt_d[2][0]) + np.square(pt_d[2][1]))
    distance[3] = np.sqrt(np.square(pt_d[3][0]) + np.square(pt_d[3][1]))

    min = distance[0]
    min_idx = 0

    for i in range (1, 4):
        if (distance[i] < min):
            min_idx = i
            min = distance[i]

    new_pt = list(new_pt)

    pts[min_idx] = new_pt

    corner1 = pts[0]
    corner2 = pts[1]
    corner3 = pts[2]
    corner4 = pts[3]

    return corner1, corner2, corner3, corner4

def paperBound(frame):
    pt1 = None
    pt2 = None
    pt3 = None
    pt4 = None
    horizs_found = False
    verts_found = False
    threshold = 0.2
    maxWidth = 1100; maxHeight = 850
    imgHeight, imgWidth = frame.shape[:2]
    hScale = 1; wScale = 1
    thickness = 1
    if imgHeight > maxHeight:
        hScale = imgHeight / maxHeight
        thickness = 6
    if imgWidth > maxWidth:
        wScale = imgWidth / maxWidth
        thickness = 6

    maxArea = frame.shape[0] * frame.shape[1]
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    vals = gray.flatten()
    b, bins, patches = plt.hist(vals, 255)

    mode = np.argmax(b)

    var = np.var(gray)
    std = np.sqrt(var)

    valleys = argrelextrema(b, np.less)
    valleys = valleys[0]

    contour_cnt = 0

    blank_image = np.zeros((frame.shape[0],frame.shape[1],3), np.uint8)

    lowest_x = blank_image.shape[1]
    lowest_y = blank_image.shape[0]

    highest_x = 0
    highest_y = 0

    tl = [None, None]
    tr = [None, None]
    bl = [None, None]
    br = [None, None]

    font = cv2.FONT_HERSHEY_COMPLEX

    width = frame.shape[1]
    height = frame.shape[0]

    contour_count = 0

    for valley in valleys:
        if (valley > mode):
            min_thresh = valley
            max_thresh = min_thresh + 35
            ret, thresh = cv2.threshold(gray, min_thresh, max_thresh, cv2.THRESH_BINARY)
            contours,hierarchy = cv2.findContours(thresh, 1, 2)

            cv2.imshow('Threshold', thresh)
            cv2.waitKey(1)

            for cnt in contours:

               x1,y1 = cnt[0][0]
               approx = cv2.approxPolyDP(cnt, 0.015*cv2.arcLength(cnt, True), True)

               if len(approx) == 4:

                  x, y, w, h = cv2.boundingRect(cnt)
                  ratio = float(w)/h
                  area = (w * h)
      
                  if (area > maxArea/10):
         
                     rect_w = w
                     rect_h = h

                     contour_cnt += 1
                     bound = cv2.drawContours(blank_image, [cnt], -1, (255,255,255), 3)
                     coord_list = cnt.ravel() 

                     i = 0

                     contour_count += 1

                     for coord in coord_list:

                        if (i % 2 == 0):
                            x1 = coord_list[i]
                            y1 = coord_list[i + 1]
                            string = str(x1) + " " + str(y1) 
                            sum_coords = x1 + y1

                        if (x1 < lowest_x):
                            pt1 = [y1, x1]
                            lowest_x = x1
                        if (x1 > highest_x):
                            pt2 = [y1, x1]
                            highest_x = x1
                        if (y1 < lowest_y):
                            pt3 = [y1, x1]
                            lowest_y = y1
                        if (y1 > highest_y):
                            pt4 = [y1, x1]
                            highest_y = y1
            
                        i+=1
            if (contour_count > 0): break

    if (pt1 is not None) and (pt2 is not None) and (pt3 is not None) and (pt4 is not None) and (bound is not None):
        return pt1, pt2, pt3, pt4, bound, rect_w, rect_h
    else: 
        bound = [[0, 0], 
        [0, 0]]
        return 0,   0,   0,   0,     bound,      0,      0
    
def paperBoundRobot(frame):

    pt1 = None
    pt2 = None
    pt3 = None
    pt4 = None
    horizs_found = False
    verts_found = False
    threshold = 0.2
    maxWidth = 1100; maxHeight = 850
    imgHeight, imgWidth = frame.shape[:2]
    hScale = 1; wScale = 1
    thickness = 1
    if imgHeight > maxHeight:
        hScale = imgHeight / maxHeight
        thickness = 6
    if imgWidth > maxWidth:
        wScale = imgWidth / maxWidth
        thickness = 6

    maxArea = frame.shape[0] * frame.shape[1]
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    vals = gray.flatten()
    b, bins, patches = plt.hist(vals, 255)

    mode = np.argmax(b)

    var = np.var(gray)
    std = np.sqrt(var)

    valleys = argrelextrema(b, np.less)
    valleys = valleys[0]

    contour_cnt = 0

    blank_image = np.zeros((frame.shape[0],frame.shape[1],3), np.uint8)

    lowest_x = blank_image.shape[1]
    lowest_y = blank_image.shape[0]

    highest_x = 0
    highest_y = 0

    tl = [None, None]
    tr = [None, None]
    bl = [None, None]
    br = [None, None]

    font = cv2.FONT_HERSHEY_COMPLEX

    width = frame.shape[1]
    height = frame.shape[0]

    contour_count = 0

    min_thresh = 1
    max_thresh = min_thresh + 35
    ret, thresh = cv2.threshold(gray, min_thresh, max_thresh, cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(thresh, 1, 2)

    cv2.imshow('Threshold', thresh)
    cv2.waitKey(1)

    for cnt in contours:

        x1,y1 = cnt[0][0]
        approx = cv2.approxPolyDP(cnt, 0.015*cv2.arcLength(cnt, True), True)

        if len(approx) == 4:

            x, y, w, h = cv2.boundingRect(cnt)
            ratio = float(w)/h
            area = (w * h)
      
            if (area > maxArea/10):
         
                rect_w = w
                rect_h = h

                contour_cnt += 1
                bound = cv2.drawContours(blank_image, [cnt], -1, (255,255,255), 3)
                coord_list = cnt.ravel() 

                i = 0

                contour_count += 1

                for coord in coord_list:

                    if (i % 2 == 0):
                        x1 = coord_list[i]
                        y1 = coord_list[i + 1]
                        string = str(x1) + " " + str(y1) 
                        sum_coords = x1 + y1

                    if (x1 < lowest_x):
                        pt1 = [y1, x1]
                        lowest_x = x1
                    if (x1 > highest_x):
                        pt2 = [y1, x1]
                        highest_x = x1
                    if (y1 < lowest_y):
                        pt3 = [y1, x1]
                        lowest_y = y1
                    if (y1 > highest_y):
                        pt4 = [y1, x1]
                        highest_y = y1
            
                    i+=1

        if (contour_count > 0): break

    if (pt1 is not None) and (pt2 is not None) and (pt3 is not None) and (pt4 is not None) and (bound is not None):
        return pt1, pt2, pt3, pt4, bound, rect_w, rect_h
    
    else: 
        bound = [[0, 0], 
        [0, 0]]
        return 0,   0,   0,   0,     bound,      0,      0


def findCorners(pt1, pt2, pt3, pt4, bound, frame, rect_w, rect_h):

    width = bound.shape[1]
    height = bound.shape[0]
    maxWidth = 1100; maxHeight = 850
    imgHeight, imgWidth = frame.shape[:2]
    hScale = 1
    wScale = 1

    if ((pt1 != 0) and (pt2 != 0) and (pt3 != 0) and (pt4 != 0)):

        pt1 = list(pt1)
        pt2 = list(pt2)
        pt3 = list(pt3)
        pt4 = list(pt4)

        rhos = [None, None, None, None]
        thetas = [None, None, None, None]

        rhos = list(rhos)
        thetas = list(thetas)

        rhos_horiz = [None, None]
        thetas_horiz = [None, None]

        rhos_horiz = list(rhos_horiz)
        thetas_horiz = list(thetas_horiz)

        rhos_vert = [None, None]
        thetas_vert = [None, None]

        rhos_vert = list(rhos_vert)
        thetas_vert = list(thetas_vert)
             
        #             x1  , y1  , x2  , y2  , dydx, vertical (T or F)
        candidate1 = [None, None, None, None, None, None]
        candidate2 = [None, None, None, None, None, None]
        candidate3 = [None, None, None, None, None, None]
        candidate4 = [None, None, None, None, None, None]

        candidates = [None, None, None, None]
        candidates = list(candidates)

        candidate1 = list(candidate1)
        candidate2 = list(candidate2)
        candidate3 = list(candidate3)
        candidate4 = list(candidate4)

        intersection = [None, None]
        intersection = list(intersection)

        cand_center = (None, None)
        cand_center = list(cand_center)

        center = (None, None)
        center = list(center)

        line_count = 0

        angle_thresh = 0.75

        bound_g = cv2.cvtColor(bound, cv2.COLOR_BGR2GRAY)
        bound_l = bound
        lines = cv2.HoughLines(bound_g, 1, np.pi / 1400, 120, None, 0, 0)
    
        for i in range(0, len(lines)):
        #################################
            rho = lines[i][0][0]
            theta = lines[i][0][1]
            a = math.cos(theta)
            b = math.sin(theta)
            x0 = a * rho
            y0 = b * rho
            pth1 = (int(x0 + 1000*(-b)), int(y0 + 1000*(a)))
            pth2 = (int(x0 - 1000*(-b)), int(y0 - 1000*(a)))

            if (pth1[0] - pth2[0] == 0):
                offset = 1
            else:
                offset = 0

            dydx = abs((pth1[1] - pth2[1] + offset) / (pth1[0] - pth2[0] + offset))

            # Vertical or horizontal lines don't necessarily correlate with slopes > or < 1. 
            # Need to take first line, and compare to subsequent lines
            # If next line has similar slope and similar coordinates, disregard
            # IF next line has similar slope and different coordinates, it is the second line of the same orientation. Only look for different slopes

            # Looking at slopes alone will make it hard to differentiate perpendicular paper bounds that aren't perceived "head-on"
            # i.e. most of the time, the angle that both perpendicular bounds make, due to the view perspective, is less than 90 degrees.
            # The slope of the lines isn't linearly related to the angle that both lines make. Taking the log base 10 of the slopes will achieve a linear 
            # this result and the angle between both lines. This way, a minimum threshold for difference in angle (difference in log result) 
            # can be set to detect perpendicular lines
            if (dydx != 0):
                logged = math.log10(dydx)
                if (line_count == 0): 
                    candidate1 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, None]
                    candidates[0] = candidate1
                    rhos[0] = rho
                    thetas[0] = theta
                    line_count += 1
                    bound_l = cv2.line(bound, (candidate1[0], candidate1[1]), (candidate1[2], candidate1[3]), (255,0,0), 3, cv2.LINE_AA)

                elif (line_count == 1):
                    if ((math.log10(candidate1[4]) - math.log10(dydx)) > angle_thresh):
                        # candidate1 is vertical, and current line is horizontal
                        candidate1[5] = True
                        candidate2 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, False]
                        candidates[1] = candidate2
                        rhos[1] = rho
                        thetas[1] = theta
                        line_count += 1
                        bound_l = cv2.line(bound, (candidate2[0], candidate2[1]), (candidate2[2], candidate2[3]), (0,255,0), 3, cv2.LINE_AA)

                    elif ((math.log10(candidate1[4]) - math.log10(dydx)) < -(angle_thresh)):
                        # candidate1 is horizontal, and current line is vertical
                        candidate1[5] = False
                        candidate2 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, True]
                        candidates[1] = candidate2
                        rhos[1] = rho
                        thetas[1] = theta
                        line_count += 1
                        bound_l = cv2.line(bound, (candidate2[0], candidate2[1]), (candidate2[2], candidate2[3]), (0,255,0), 3, cv2.LINE_AA)

                    elif (angle_thresh > (math.log10(candidate1[4]) - math.log10(dydx)) > -(angle_thresh)):
                        # check to see if lines are parallel (not the same line)
                        intersection[0], intersection[1] = houghIntersection(thetas[0], rhos[0], theta, rho)

                        if (intersection[0] != 0) and (intersection[1] != 0):

                            if not ((-150 < intersection[0] < width + 150) or (-150 < intersection[1] < height + 150)):
                                # if intersection is out of frame, lines are different
                                candidate2 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, candidate1[5]]
                                candidates[1] = candidate2
                                rhos[1] = rho
                                thetas[1] = theta
                                line_count += 1
                                bound_l = cv2.line(bound, (candidate2[0], candidate2[1]), (candidate2[2], candidate2[3]), (0,255,0), 3, cv2.LINE_AA)
                        
                elif (line_count == 2):
                    # 2 possibilities: 
                        # 2 previous lines are parallel but different lines
                        # 2 previous lines have different orientations
                            # If lines are vertical, check x coordinates
                            # If lines are horizontal, check y-coordinates
                            # If unknown to be vertical or horizontal, compare current line's orientation to both previous lines
                                # Note math.log10 of each line, current imclusive
                                # Set line(s) with lowest slipe to horizontal
                                # Set line(s) with highest slope to vertical

                    if (candidate1[5] is None) and (candidate2[5] is None):
                        if (math.log10(candidate1[4]) - math.log10(dydx) > angle_thresh):
                        # candidates 1 and 2 are vertical, and current line is horizontal
                            candidate1[5] = True
                            candidate2[5] = True
                            candidate3 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, False]
                            candidates[2] = candidate3
                            rhos[2] = rho
                            thetas[2] = theta
                            line_count += 1
                            bound_l = cv2.line(bound, (candidate3[0], candidate3[1]), (candidate3[2], candidate3[3]), (0,0,255), 3, cv2.LINE_AA)

                        elif (math.log10(candidate1[4]) - math.log10(dydx) < -(angle_thresh)):
                            # candidates 1 and 2 are horizontal, and current line is vertical
                            candidate1[5] = False
                            candidate2[5] = False
                            candidate3 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, True]
                            candidates[2] = candidate3
                            rhos[2] = rho
                            thetas[2] = theta

                            line_count += 1
                            bound_l = cv2.line(bound, (candidate3[0], candidate3[1]), (candidate3[2], candidate3[3]), (0,0,255), 3, cv2.LINE_AA)
                            # else do nothing, 

                    else:

                        closer_to_1 = abs(math.log10(dydx) - math.log10(candidate1[4]))
                        closer_to_2 = abs(math.log10(dydx) - math.log10(candidate2[4]))
                        slope_eq_1 = (angle_thresh > abs(math.log10(candidate1[4]) - math.log10(dydx)))
                        slope_eq_2 = (angle_thresh > abs(math.log10(candidate2[4]) - math.log10(dydx)))
                        
                        if (slope_eq_1):

                            intersection[0], intersection[1] = houghIntersection(thetas[0], rhos[0], theta, rho)
                            if (intersection[0] != 0) and (intersection[1] != 0):
                                multiplier = 1#1/ 0.001 + abs(math.log10(candidate1[4]) - math.log10(dydx))
                                if not ((-150 < intersection[0] < width) or (-150 < intersection[1] < height)):
                                        # if intersection is out of frame, lines are different
                                    candidate3 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, candidate1[5]]
                                    candidates[2] = candidate3
                                    rhos[2] = rho
                                    thetas[2] = theta
                                    line_count += 1
                                    bound_l = cv2.line(bound, (candidate3[0], candidate3[1]), (candidate3[2], candidate3[3]), (0,0,255), 3, cv2.LINE_AA)

                        elif(slope_eq_2):
                                # New line is closer to line 2. Compare distances
                            intersection[0], intersection[1] = houghIntersection(thetas[1], rhos[1], theta, rho)
                            if (intersection[0] != 0) and (intersection[1] != 0):
                                
                                multiplier = 1#1/ 0.001 + abs(math.log10(candidate1[4]) - math.log10(dydx))
                                if not ((-10 < intersection[0] < width) or (-10  < intersection[1] < height)):
                                        # if intersection is out of frame, lines are different
                                    candidate3 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, candidate2[5]]
                                    candidates[2] = candidate3
                                    rhos[2] = rho
                                    thetas[2] = theta
                                    line_count += 1
                                    bound_l = cv2.line(bound, (candidate3[0], candidate3[1]), (candidate3[2], candidate3[3]), (0,0,255), 3, cv2.LINE_AA)

                elif (line_count == 3):

                     closer_to_1 = abs(math.log10(dydx) - math.log10(candidate1[4]))
                     closer_to_2 = abs(math.log10(dydx) - math.log10(candidate2[4]))
                     closer_to_3 = abs(math.log10(dydx) - math.log10(candidate3[4]))

                     orientations = [None, None, None]
                     orientations = list(orientations)
                     orientations[0] = candidate1[5]
                     orientations[1] = candidate2[5]
                     orientations[2] = candidate3[5]
                        
                     if (orientations[0] == orientations[1]):
                        target = candidate3   # only look at candidate3   110 or 001
                        t_rho = rhos[2]
                        t_theta = thetas[2]
                        color = "red"
                     elif (orientations[0] == orientations[2]):
                        target = candidate2 # only look at candidate2  101 or 010
                        t_rho = rhos[1]
                        t_theta = thetas[1]
                        color = "green"
                     else:
                        target = candidate1 # orientations[0] is the outlier, only look at candidate[0]
                        t_rho = rhos[0]
                        t_theta = thetas[0]
                        color = "blue"

                     slope_eq = (angle_thresh > abs(math.log10(target[4]) - math.log10(dydx)))

                     # 100, 010, 001
                     # or
                     # 011, 101, 110
                        
                     if slope_eq: # If slope is the same as the line without a parallel line
                         intersection[0], intersection[1] = houghIntersection(t_theta, t_rho, theta, rho)
                         if (intersection[0] != 0) and (intersection[1] != 0):
                            multiplier = 1#1/ 0.001 + abs(math.log10(candidate1[4]) - math.log10(dydx))
                            if not ((-10 < intersection[0] < width) or (-10 < intersection[1] < height)):
                                # if intersection is out of frame, lines are different
                                candidate4 = [pth1[0], pth1[1], pth2[0], pth2[1], dydx, target[5]]
                                candidates[3] = candidate4
                                rhos[3] = rho
                                thetas[3] = theta
                                line_count += 1
                                bound_l = cv2.line(bound, (pth1[0], pth1[1]), (pth2[0], pth2[1]), (0,255,255), 3, cv2.LINE_AA)
                else:
  
                    break

        defined_lines = 0

        for i in range(0, 4):
            if (candidates[i] is None): break
            if (candidates[i][5] == True): # Vertical line
                defined_lines += 1
                if (rhos_vert[0] is None):
                    rhos_vert[0] = rhos[i]
                    thetas_vert[0] = thetas[i]
                else:
                    rhos_vert[1] = rhos[i]
                    thetas_vert[1] = thetas[i]
            elif (candidates[i][5] == False): # Horizontal line
                defined_lines += 1
                if (rhos_horiz[0] is None):
                    rhos_horiz[0] = rhos[i]
                    thetas_horiz[0] = thetas[i]
                else:
                    rhos_horiz[1] = rhos[i]
                    thetas_horiz[1] = thetas[i]

        pt1_c = pt1
        pt2_c = pt2
        pt3_c = pt3
        pt4_c = pt4

        if (defined_lines == 4):

            # 4 intersections (4 points) defined
            pt1 = houghIntersection(thetas_horiz[0], rhos_horiz[0], thetas_vert[0], rhos_vert[0])
            pt2 = houghIntersection(thetas_horiz[0], rhos_horiz[0], thetas_vert[1], rhos_vert[1])
            pt3 = houghIntersection(thetas_horiz[1], rhos_horiz[1], thetas_vert[0], rhos_vert[0])
            pt4 = houghIntersection(thetas_horiz[1], rhos_horiz[1], thetas_vert[1], rhos_vert[1])

            pt1 = swapCoords(pt1)
            pt2 = swapCoords(pt2)
            pt3 = swapCoords(pt3)
            pt4 = swapCoords(pt4)

        elif (defined_lines == 3):

            # 2 intersections (2 points) defined
            # tl and bl or tr and br
            # if y-coordinates are closer than x-coords, tl and tr or bl and br
            # else, tl and bl or tr and br

            # should compare to 4 points found below
            pt1_t = houghIntersection(thetas_horiz[0], rhos_horiz[0], thetas_vert[0], rhos_vert[0]) 
            pt1_t = swapCoords(pt1_t)
            pt1, pt2, pt3, pt4 = replaceClosestCorner(pt1_t, pt1, pt2, pt3, pt4)
            
            if (rhos_horiz[1] is not None):
                # tl and bl or tr and br
                pt2_t = houghIntersection(thetas_horiz[1], rhos_horiz[1], thetas_vert[0], rhos_vert[0])
                pt2_t = swapCoords(pt2_t)
                pt1, pt2, pt3, pt4 = replaceClosestCorner(pt2_t, pt1, pt2, pt3, pt4)
                

            elif (rhos_vert[1] is not None):
                pt2_t = houghIntersection(thetas_horiz[0], rhos_horiz[0], thetas_vert[1], rhos_vert[1])
                # tl and tr or bl and br
                pt2_t = swapCoords(pt2_t)
                pt1, pt2, pt3, pt4 = replaceClosestCorner(pt2_t, pt1, pt2, pt3, pt4)

        elif (defined_lines == 2):
            if (candidates[0][5] != candidates[1][5]):
                # 1 intersection, could be any point
                pt1_t = houghIntersection(thetas_horiz[0], rhos_horiz[0], thetas_vert[0], rhos_vert[0])
                pt1_t = swapCoords(pt1_t)
                pt1, pt2, pt3, pt4 = replaceClosestCorner(pt1_t, pt1, pt2, pt3, pt4)

        hy_hx = [pt4[0] - pt2[0], pt4[1] - pt2[1]]
        hyp_1 = np.sqrt(np.square(hy_hx[0]) + np.square(hy_hx[1]))

        ly_hx = [pt3[0] - pt2[0], pt3[1] - pt2[1]]
        hyp_2 = np.sqrt(np.square(ly_hx[0]) + np.square(ly_hx[1]))

        if (hyp_1 > hyp_2):
            tl = pt3
            tl_c = pt3_c

            tr = pt2
            tr_c = pt2_c

            bl = pt1
            bl_c = pt1_c

            br = pt4
            br_c = pt4_c
        else:

            tl = pt1
            tl_c = pt1_c

            tr = pt3
            tr_c = pt3_c

            bl = pt4
            bl_c = pt4_c

            br = pt2
            br_c = pt2_c

       # Find intersection here
        cv2.circle(bound, (tl[1], tl[0]), 5, (0, 255, 255), -1)
        cv2.circle(bound, (tr[1], tr[0]), 5, (0, 255, 255), -1)
        cv2.circle(bound, (bl[1], bl[0]), 5, (0, 255, 255), -1)
        cv2.circle(bound, (br[1], br[0]), 5, (0, 255, 255), -1)

        tl = list(tl)
        tr = list(tr)
        bl = list(bl)
        br = list(br)

        tl = swapCoords(tl)
        tr = swapCoords(tr)
        bl = swapCoords(bl)
        br = swapCoords(br)

        center = [height // 2, width //2]
        bl_tfm = [center[1] - (rect_w // 8), center[0] + (rect_h // 8)]
        br_tfm = [center[1] + (rect_w // 8), center[0] + (rect_h // 8)]
        tl_tfm = [center[1] - (rect_w // 8), center[0] - (rect_h // 8)]
        tr_tfm = [center[1] + (rect_w // 8), center[0] - (rect_h // 8)]

        imgPts = np.float32([tl, tr, bl, br])
        imgPts_c = np.float32([tl_c, tr_c, bl_c, br_c])

        test_tl = (0, 0)
        test_tr = (width, 0)
        test_bl = (0, height)
        test_br = (width, height)

        objPts = np.float32([test_tl, test_tr, test_bl, test_br])

        matrix = cv2.getPerspectiveTransform(imgPts, objPts)
        matrix_c = cv2.getPerspectiveTransform(imgPts_c, objPts)

        blank_image = np.zeros((850,1100,3), np.uint8)

        result = cv2.warpPerspective(frame, matrix, (width, height))
        result_c = cv2.warpPerspective(frame, matrix, (width, height))

        if hScale > wScale:
            bound = cv2.resize(bound, (int(imgWidth / hScale), maxHeight))
        elif hScale < wScale:
            bound = cv2.resize(bound, (maxWidth, int(imgHeight / wScale)))

        cv2.imshow('Thresh', bound_l)
        cv2.waitKey(1)

        gray_qr = cv2.cvtColor(result, cv2.COLOR_BGR2GRAY)
        gray_qr_c = cv2.cvtColor(result_c, cv2.COLOR_BGR2GRAY)
        
        vals = gray_qr.flatten()
        b, bins, patches = plt.hist(vals, 255)
        plt.xlim([0,255])

        mode = np.argmax(b)

        ret, gray_qr = cv2.threshold(gray_qr, 100, 255, cv2.THRESH_BINARY)
        code = postprocess(gray_qr)

        if (code is None):
            code = postprocess(gray_qr_c)

def detectEntrance(frame):
            
    err_bound = np.empty((2,2))

    retval_detected = 0
    retval_mat = err_bound

    maxWidth = 1100; maxHeight = 850
    imgHeight, imgWidth = frame.shape[:2]

    hScale = 1
    wScale = 1

    frame = cv2.rotate(frame, cv2.ROTATE_180)

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) 

    lower_red1 = np.array([0, 85, 85]) 
    upper_red1 = np.array([8, 255, 255]) 
    mask1 = cv2.inRange(hsv, lower_red1, upper_red1) 

    lower_red2 = np.array([170, 85, 85]) 
    upper_red2 = np.array([179, 255, 255]) 
    mask2 = cv2.inRange(hsv, lower_red2, upper_red2) 

    mask = cv2.bitwise_or(mask1, mask2) 

    red_img = cv2.bitwise_and(frame, frame, mask = mask) 

    edges = cv2.Canny(red_img, 100, 200, None, 3) 

    if hScale > wScale: 
        edges = cv2.resize(edges, (int(imgWidth / hScale), maxHeight)) 

    elif hScale < wScale: 
        edges = cv2.resize(edges, (maxWidth, int(imgHeight / wScale))) 

    cv2.imshow('Edges', edges) 
    cv2.waitKey(1) 

    col_edges = cv2.cvtColor(edges, cv2.COLOR_GRAY2BGR)
    lines = cv2.HoughLines(edges, 1, np.pi / 750, 100, None, 0, 0)

    if lines is not None: 

        for i in range(0, len(lines)): 

            rho = lines[i][0][0] 
            theta = lines[i][0][1] 

            a = math.cos(theta) 
            b = math.sin(theta) 

            x0 = a * rho 
            y0 = b * rho 

            pt1 = (int(x0 + 1000*(-b)), int(y0 + 1000*(a))) 
            pt2 = (int(x0 - 1000*(-b)), int(y0 - 1000*(a))) 
            
            col_edges = cv2.line(col_edges, pt1, pt2, (0, 255, 0), 3, cv2.LINE_AA)

    if (lines is not None):   
        retval_detected = 1
        print('Len(lines): {}'.format(len(lines)))
        print('Entrance found.')
        return retval_detected, col_edges

    else:
        retval_detected = 0
        return retval_detected, retval_mat
        
