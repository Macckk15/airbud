import numpy as np
import cv2
from start_cameras import Start_Cameras
import qr_funcs

left_camera = Start_Cameras(0).start()

print("mason")

# may need a way to tell if camera not opened
err_bound =[[0, 0], 
            [0, 0]]

while True:

    # Capture frame-by-frame
    left_grabbed, left_frame = left_camera.read()

    # if frame is read correctly ret is True
    if not (left_grabbed):
        print("Can't receive frame (stream end?). Exiting ...")
    # Our operations on the frame come here
    
    cv2.imshow('frame', left_frame)
    cv2.waitKey(1)

    gray_qr = cv2.cvtColor(left_frame, cv2.COLOR_BGR2GRAY)

    qr_funcs.postprocess(gray_qr)
    #pt1, pt2, pt3, pt4, bound, rect_w, rect_h = qr_funcs.paperBound(left_frame)
    #if (bound != err_bound):
        
        #qr_funcs.findCorners(pt1, pt2, pt3, pt4, bound, left_frame, rect_w, rect_h)
    # Display the resulting frame
    if cv2.waitKey(1) == ord('q'):
        break

# When everything done, release the capture
left_camera.stop()
left_camera.release()
cv2.destroyAllWindows()
