import cv2
import numpy as np
import sys

if len(sys.argv) < 2:
    sys.exit('Usage: %s photo name' % sys.argv[0])

template='photos/'+sys.argv[1]
image=template+'_template'+'.jpg'
template+='.jpg'

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


for h,des in enumerate(desc):
    des = np.array(des,np.float32).reshape((1,-1)) #the -1 was originally 128 which was throwing up an instance because it needed to change the array's size to obtain the desired output matrix!
    retval, results, neigh_resp, dists = knn.find_nearest(des,1)
    res,dist =  int(results[0][0]),dists[0][0]

    if dist<0.01: # draw matched keypoints in red color
        color = (0,0,255)
	
    else:  # draw unmatched in blue color
        print dist
        color = (255,0,0)

    #Draw matched key points on original image
    x,y = kp[res].pt
    center = (int(x),int(y))
    cv2.circle(img,center,2,color,-1)

    #Draw matched key points on template image
    x,y = keys[h].pt
    center = (int(x),int(y))
    cv2.circle(template,center,2,color,-1)

cv2.imshow('img',img)
cv2.imshow('tm',template)
cv2.waitKey(0)
cv2.destroyAllWindows()
