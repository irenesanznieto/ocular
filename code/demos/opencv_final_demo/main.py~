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
	cv2.destroyWindow('TEMPLATE OBJECTS CAPTURE')

else: 
	templates_num= len([ f for f in listdir('templates_data') if isfile(join('templates_data',f)) ])


#Match objects
init=time.time()

print 'To capture each new object, please press the space bar'

while True: 
	ret, im=cap.read()
	cv2.imshow('MATCHING OBJECTS', im)
	key=cv2.waitKey(10)
	if key ==27: 
		break
	if key ==ord(' '): 
		cv2.imwrite('dummy.jpg', im)
		break

#Comparison of the obtained image with the templates
num=0

percentage=[]
while num<templates_num:
	name='template'+str(num)+'.jpg'
	percentage.append(surf.compare_images('dummy.jpg',name, 0.05))
	num+=1


id_object = np.argmax(percentage)

end=time.time()

cv2.destroyWindow('MATCHING OBJECTS')


#Show result
print '\n\n\nRESULTS\n.............\nThe ratios of similarity are the following: ', percentage, 'The object is more similar to template', id_object,  '\nTotal computing time: ', (end-init), 's'
cv2.imshow('New Object',cv2.imread('templates_data/temporal/dummy.jpg'))
template_path='templates_data/temporal/template'+str(id_object)+'.jpg'
cv2.imshow('Template Match',cv2.imread(template_path))

#remove dummy files
os.remove("dummy.jpg")
rmfiles_in_folder("templates_data/temporal/")


cv2.waitKey(0)
cv2.destroyAllWindows()





