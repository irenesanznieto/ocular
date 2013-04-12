import surf
import os
import cv2
import time
from os import listdir
from os.path import isfile, join
import numpy as np
import shutil


def rmfiles_in_folder (path):
	dummyfiles= [ f for f in listdir(path) if isfile(join(path,f)) ]
	for k in dummyfiles: 
		os.remove(path+k)




#Instructions

choice=raw_input("OPENCV-PYTHON DEMO\n ..................\nType 1 to obtain new templates\nType any other key to keep the previous ones\n")

#Video Capture
cap=cv2.VideoCapture(0)

#New Templates
if (choice =='1'):

	templates_num=int(raw_input("Enter the number of templates of this program\n"))
	
	print 'To capture each template please press the space bar. The web cam window will close after all captures have been obtained'
	num=0
	rmfiles_in_folder('templates_data/')
	while num!=templates_num: 
		ret, im=cap.read()
		cv2.imshow('TEMPLATE OBJECTS CAPTURE', im)
		key=cv2.waitKey(100)
		if key ==27: 
			break
		if key ==ord(' '): 
			name='templates_data/template'+str(num)
			name+='.jpg'
			cv2.imwrite(name, im)
			num+=1
			print 'TEMPLATE', num, 'CAPTURED'
	cv2.destroyWindow('TEMPLATE OBJECTS CAPTURE')

else: 
	templates_num= len([ f for f in listdir('templates_data') if isfile(join('templates_data',f)) ])


#Match objects
init=time.time()

print 'To capture the new object, please press the space bar'

while True: 
	ret, im=cap.read()
	cv2.imshow('MATCHING OBJECTS', im)
	key=cv2.waitKey(10)
	if key ==27: 
		break
	if key ==ord(' '): 
		cv2.imwrite('dummy.jpg', im)
		print 'Object CAPTURED'
		break

#Comparison of the obtained image with the templates
num=0

lap_per=[] #laplacian percentage
nor_per=[] #normal percentage	
accuracy=0.1

while num<templates_num:
	name='template'+str(num)+'.jpg'
	lap_per.append(surf.compare_images('dummy.jpg',name, accuracy, True))
	nor_per.append(surf.compare_images('dummy.jpg',name, accuracy, False))
	num+=1

id_lap=np.argmax(lap_per)
id_nor=np.argmax(nor_per)

end=time.time()

cv2.destroyWindow('MATCHING OBJECTS')


#Print result
print '\n\n\nRESULTS\n.............\nThe ratios of similarity are the following:\nComputing the Laplacian of the image: ', lap_per, '\nObtaining the descriptors directly from the image: ', nor_per, '\n\nThe object is more similar to:\nLaplacian: template', id_lap, lap_per[id_lap], '\nNormal: template', id_nor, nor_per[id_nor],'\n\nTotal computing time: ', (end-init), 's'


#Show result
cv2.imshow('New Object',cv2.imread('templates_data/temporal/dummy.jpg'))

template_lap='templates_data/temporal/template'+str(id_lap)+'.jpg'
cv2.imshow('Template Match LAPLACIAN',cv2.imread(template_lap))

template_nor='templates_data/temporal/template'+str(id_nor)+'.jpg'
cv2.imshow('Template Match NORMAL',cv2.imread(template_nor))

#remove dummy files
os.remove("dummy.jpg")
rmfiles_in_folder("templates_data/temporal/")


cv2.waitKey(0)
cv2.destroyAllWindows()

