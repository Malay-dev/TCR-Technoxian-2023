import cv2
import cv2.aruco as aruco
import numpy as np


aruco_id = 0
aruco_distance =0
aruco_angle = []
x=0
y=0




def ID():
    return aruco_id


def DISTANCE():
    return aruco_distance


def ANGLE():
    return aruco_angle


def CO_ORDINATES():
    return x, y


def findAruco(img, marker_size=6, total_markers=250, draw=True):
    flag = 0
    global aruco_id
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    key = getattr(aruco, f'DICT_{marker_size}X{marker_size}_{total_markers}')
    ARUCO_DICT = aruco.Dictionary_get(key)
    ARUCO_PARAMS = aruco.DetectorParameters_create()
    corners, ids, reject = aruco.detectMarkers(
        gray, ARUCO_DICT, parameters=ARUCO_PARAMS)
    if draw:
        aruco.drawDetectedMarkers(img, corners)
        if corners:
            aruco_id=ids[0]
            corners = np.array(corners)[0]
            top_right = corners[0][1][0], corners[0][1][1]
            cv2.putText(
                img,
                f"id: {ids[0]}",
                np.array(top_right).astype(int),
                cv2.FONT_HERSHEY_PLAIN,
                1.3,
                (0, 0, 255),
                2,
                cv2.LINE_AA,
            )
            flag = 1
    return ARUCO_DICT, ARUCO_PARAMS, flag


def distance_pose(img, ARUCO_DICT, ARUCO_PARAMS):
    global aruco_distance, aruco_angle, x, y
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    corners, ids, reject = aruco.detectMarkers(
        gray, ARUCO_DICT, parameters=ARUCO_PARAMS)
    if corners:
        # LOADING CAMERA CALIBRATION FILE
        calib_data_path = "Aruco\Camera Callibration\calib_data\MultiMatrix.npz"
        calib_data = np.load(calib_data_path)
        camera_matrix = calib_data["camMatrix"]
        distance_coefficient = calib_data["distCoef"]
        MARKER_SIZE = 8
        rVec, tVec, _ = aruco.estimatePoseSingleMarkers(
            corners, MARKER_SIZE, camera_matrix, distance_coefficient
        )

        for i in range(ids.size):
            cv2.drawFrameAxes(img, camera_matrix,
                              distance_coefficient,  rVec[i], tVec[i], 4, 4)
            if corners:
                x=round(tVec[i][0][0], 1)
                y=round(tVec[i][0][1], 1)
                corners = np.array(corners)[0]
                bottom_right = corners[0][2][0], corners[0][2][1]
                cv2.putText(
                    img,
                    f"x:{round(tVec[i][0][0],1)} y: {round(tVec[i][0][1],1)} ",
                    np.array(bottom_right).astype(int),
                    cv2.FONT_HERSHEY_PLAIN,
                    1.0,
                    (0, 0, 255),
                    2,
                    cv2.LINE_AA,
                )
                rmat, jac = cv2.Rodrigues(rVec)
                angles, mtxR, mtxQ, Qx, Qy, Qz = cv2.RQDecomp3x3(rmat)
                aruco_angle=angles[1]
                distance = np.sqrt(
                    tVec[i][0][2] ** 2 +
                    tVec[i][0][0] ** 2 + tVec[i][0][1] ** 2
                )
            aruco_distance=distance
            bottom_left = corners[0][3][0], corners[0][3][1]
            cv2.putText(
                img,
                f"Dist: {round(distance, 2)}",
                np.array(bottom_left).astype(int),
                cv2.FONT_HERSHEY_PLAIN,
                1.3,
                (0, 0, 255),
                2,  cv2.LINE_AA,
            )



