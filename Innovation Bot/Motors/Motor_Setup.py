import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# MOTOR LEFT
AN1 = 15
DIG1 = 14

# MOTOR RIGHT
AN2 = 23
DIG2 = 18


# MOTOR SETUP
GPIO.setup(AN1, GPIO.OUT)
GPIO.setup(DIG1, GPIO.OUT)
GPIO.setup(AN2, GPIO.OUT)
GPIO.setup(DIG2, GPIO.OUT)

p1 = GPIO.PWM(AN1, 100)			# set pwm for M1		# set pwm for M2
p2 = GPIO.PWM(AN2, 100)			# set pwm for M3		# set pwm for M4

# "" INITAL VALUE -- STOP ""    # Direction can ignore
GPIO.output(DIG1, GPIO.HIGH)     # Direction can ignore
GPIO.output(DIG2, GPIO.HIGH)
p1.start(0)                          # set speed for M1 at 0%
p2.start(0)


def FORWARD(pwm_value):
    print("move forward")
    GPIO.output(DIG1, GPIO.HIGH)
    GPIO.output(DIG2, GPIO.HIGH)
    p1.start(pwm_value)
    p2.start(pwm_value)


def BACKWARD(pwm_value):
    print("move backward")
    GPIO.output(DIG1, GPIO.LOW)
    GPIO.output(DIG2, GPIO.LOW)
    p1.start(pwm_value)
    p2.start(pwm_value)


def LEFT(pwm_value):
    print("move left")
    GPIO.output(DIG1, GPIO.HIGH)
    GPIO.output(DIG2, GPIO.LOW)
    p1.start(pwm_value)
    p2.start(pwm_value)


def RIGHT(pwm_value):
    print("move right")
    GPIO.output(DIG1, GPIO.LOW)
    GPIO.output(DIG2, GPIO.HIGH)
    p1.start(pwm_value)
    p2.start(pwm_value)


def STOP():
    print("Stop")
    GPIO.output(DIG1, GPIO.LOW)
    GPIO.output(DIG2, GPIO.LOW)
    p1.start(0)
    p2.start(0)


def ROTATE_LEFT(pwm_value):
    print("Rotate left")
    GPIO.output(DIG1, GPIO.HIGH)
    GPIO.output(DIG2, GPIO.LOW)
    p1.start(pwm_value)
    p2.start(pwm_value)


def ROTATE_RIGHT(pwm_value):
    print("Rotate right")
    GPIO.output(DIG1, GPIO.LOW)
    GPIO.output(DIG2, GPIO.HIGH)
    p1.start(pwm_value)
    p2.start(pwm_value)
