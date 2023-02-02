import cv2
import numpy as np
import matplotlib.pyplot as plt
o = cv2.imread('sample1.jpg')
im_grey = cv2.cvtColor(o, cv2.COLOR_BGR2GRAY) # 灰階影像
t, binary_img = cv2.threshold(im_grey, 140, 255, cv2.THRESH_BINARY_INV)
contours, hierarchy = cv2.findContours(binary_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cv2.drawContours(o, contours, -1, (0, 0, 255), 5)
plt.subplot(1,2,1), plt.imshow(im_grey, cmap='gray')
plt.title('original gray image')
plt.subplot(1,2,2), plt.imshow(o, cmap='gray')
plt.title('find contour result')
plt.show()