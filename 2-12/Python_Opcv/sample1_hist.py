import cv2
import matplotlib.pyplot as plt
o = cv2.imread('sample1.jpg')
im_grey = cv2.cvtColor(o, cv2.COLOR_BGR2GRAY) # 灰階影像
plt.subplot(1,2,1), plt.imshow(im_grey, cmap = 'gray')
plt.title('im_grey')
plt.subplot(1,2,2), plt.hist(im_grey.ravel(), 256)
plt.title('Histogram')
plt.show()