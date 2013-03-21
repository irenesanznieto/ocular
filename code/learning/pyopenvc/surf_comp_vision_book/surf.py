import cv2
import numpy as np

im=cv2.imread('test2.jpg')

#1/2 original size: 
im_lowres=cv2.pyrDown(im)

#gray version of the reduced image:
gray = cv2.cvtColor(im_lowres, cv2.COLOR_RGB2GRAY)

#feature detection points
s=cv2.SURF()
mask=np.uint8(np.ones(gray.shape))
keypoints=s.detect(gray, mask)

#the image may be returned to color inverting : cv2.COLOR_RGB2GRAY to cv2.COLOR_GRAY2BGR ;)
final=cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)

#print the keypoints:
for k in keypoints[::10]:
	cv2.circle(final, (int(k.pt[0]), int(k.pt[1])), 2, (0,255,0),-1) 
	cv2.circle(final, (int(k.pt[0]), int(k.pt[1])), int(k.size), (0,255,0),2) 

#different stages of the image processing: 

#cv2.imshow('ORIGINAL IMAGE', im)
#cv2.imshow('REDUCED IMAGE', im_lowres)
#cv2.imshow('GRAYSCALE', gray)
cv2.imshow('LOCAL DESCRIPTORS', final)


#common to all programs part wich waits for the user to press any key and then close all opened windows
cv2.waitKey()
cv2.closeallwindows()

