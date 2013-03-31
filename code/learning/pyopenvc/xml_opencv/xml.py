import cv2
import numpy as np

img = cv2.cv.LoadImage('star.png',0)
cv2.cv.Save('sof.xml',img)
e=cv2.cv.Load("sof.xml")

print e
