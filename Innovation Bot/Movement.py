import sys
import cv2
sys.path.append("./ArUco")
sys.path.append("./Motors")

from Motor_Setup import *
from Detect_Aruco import ID, DISTANCE, CO_ORDINATES, ANGLE, findAruco, distance_pose

kp = 15
kd = 20
ki = 0.02

priError = 0
toError = 0


def mapping(value, x, y, a, b):
    res = abs(b-a)/(y-x)
    return res*value


def PID(x):
    print("Aligning Aruco")
    global priError
    global toError
    if x != None:
        curr_x = x
        set_x = 0
        error = set_x - curr_x
        Pvalue = error * kp
        Ivalue = toError * ki
        Dvalue = (error - priError) * kd
        PIDvalue = Pvalue + Ivalue + Dvalue
        priError = error
        toError = error + toError
        res_val = abs(mapping(PIDvalue, -500, 500, 0, 100))
        if(res_val > 100):
            res_val = 50
        print(res_val)
       
        
        if x > 10:
            # RIGHT
            RIGHT(res_val)
        elif x < 10:
            # LEFT
            LEFT(res_val)
        
            
      


VideoCap = True
capture = cv2.VideoCapture(0)
while True:
    flag = 0
    if VideoCap:
        _, frame = capture.read()
        # frame = cv2.resize(frame, (0, 0), fx=0.7, fy=0.7)
        ARUCO_DICT, ARUCO_PARAMS, flag = findAruco(frame)
        distance_pose(
            frame, ARUCO_DICT=ARUCO_DICT, ARUCO_PARAMS=ARUCO_PARAMS)
        cv2.imshow("Bot Feed", frame)
        x,y = CO_ORDINATES()
        d = DISTANCE()
        if flag:
            if x and d>40:
                PID(x)
                if(x > -10 and x<10):
                    FORWARD(50)
                print(ID())
                print(x)
        else:
            STOP()

        if cv2.waitKey(1) == 113:

            break
cv2.destroyAllWindows()
