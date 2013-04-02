import cv2
import numpy as np

def compare_images (image, template_without_path, distance): 

	template='templates_data/'+template_without_path
	# Load the images
	img =cv2.imread(image)

	# Convert them to grayscale
	imgg =cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

	# SURF extraction
	surf = cv2.FeatureDetector_create("SURF")
	surfDescriptorExtractor = cv2.DescriptorExtractor_create("SURF")
	kp = surf.detect(imgg)
	kp, descriptors = surfDescriptorExtractor.compute(imgg,kp)

	# Setting up samples and responses for kNN
	samples = np.array(descriptors)
	responses = np.arange(len(kp),dtype = np.float32)

	# kNN training
	knn = cv2.KNearest()
	knn.train(samples,responses)

	# Now loading a template image and searching for similar keypoints
	template = cv2.imread(template)
	templateg= cv2.cvtColor(template,cv2.COLOR_BGR2GRAY)
	keys = surf.detect(templateg)
	keys,desc  = surfDescriptorExtractor.compute(templateg,keys)


	matched=0
	no_matched=0

	for h,des in enumerate(desc):
	    des = np.array(des,np.float32).reshape((1,-1)) #the -1 was originally 128 which was throwing up an instance because it needed to change the array's size to obtain the desired output matrix!
	    retval, results, neigh_resp, dists = knn.find_nearest(des,1)
	    res,dist =  int(results[0][0]),dists[0][0]

	    if dist<distance: # draw matched keypoints in red color
		color = (0,0,255)
		matched+=1
	
	    else:  # draw unmatched in blue color
		#print dist
		color = (255,0,0)
		no_matched+=1

	    #Draw matched key points on original image
	    x,y = kp[res].pt
	    center = (int(x),int(y))
	    cv2.circle(img,center,2,color,-1)

	    #Draw matched key points on template image
	    x,y = keys[h].pt
	    center = (int(x),int(y))
	    cv2.circle(template,center,2,color,-1)

	image_='templates_data/temporal/'
	template_=image_
	image_+=image
	template_+=template_without_path

	cv2.imwrite(image_, img)
	cv2.imwrite(template_, template)
	if no_matched==0:
		no_matched=0.0000000001

	return float(matched/float(no_matched))


