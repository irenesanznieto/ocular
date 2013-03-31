import surf
import sys
import cv2
import time

init=time.time()
if len(sys.argv) < 2:
    sys.exit('Usage: %s photo name' % sys.argv[0])

template=sys.argv[1]
image=template+'_template'+'.jpg'
template+='.jpg'
surf.compare_images(image, template)
end=time.time()

print 'Total executation time: ', (end-init), 's'
cv2.waitKey(0)
cv2.destroyAllWindows()
