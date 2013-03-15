'''		contour.py
	Test to find the contour and adjust it to a defined form

	TODO: adapt this test to recognize a brand
'''

import numpy as np
import cv2
 
im= cv2.imread('test.jpg')	#read image

imgray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)	#gray image

ret,thresh = cv2.threshold(imgray,127,255,0)
contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

cv2.drawContours(im,contours,-1,(0,255,0),3) #draw contour

len(contours)
cnt=contours[0]

perimeter = cv2.arcLength(cnt,True)
area = cv2.contourArea(cnt)
print "The perimeter is (px):", perimeter, "The area is (px):",area

cv2.imshow('CONTOURS',im)


cv2.waitKey(0)                           ## Wait for keystroke
cv2.destroyAllWindows()                  ## Destroy all windows
