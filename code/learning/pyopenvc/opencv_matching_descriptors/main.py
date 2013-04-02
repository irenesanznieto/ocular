import surf
import sys
import cv2
import time

init=time.time()
if len(sys.argv) < 2:
    sys.exit('Usage: %s photo name' % sys.argv[0])

image=sys.argv[1]
template=image+'_template'+'.jpg'
image+='.jpg'
surf.compare_images(image, template)
end=time.time()

print '\n\nDATA\n','---------------\n' 'Total computing time: ', (end-init), 's'
cv2.waitKey(0)
cv2.destroyAllWindows()
