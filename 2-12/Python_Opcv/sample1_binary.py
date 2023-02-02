import cv2
import matplotlib.pyplot as plt
o = cv2.imread('sample1.jpg')
im_grey = cv2.cvtColor(o, cv2.COLOR_BGR2GRAY) # 灰階影像
t, rst = cv2.threshold(im_grey, 140, 255, cv2.THRESH_BINARY_INV)
plt.subplot(1,2,1), plt.imshow(im_grey, cmap = 'gray')
plt.title('im_grey')
plt.subplot(1,2,2), plt.imshow(rst, cmap = 'gray')
plt.title('binary')
plt.show()
