import cv2
import matplotlib.pyplot as plt
im_grey = cv2.imread('im_grey.jpg')
cv2.imshow('im_grey', im_grey)
plt.hist(im_grey.ravel(), 256)
cv2.imshow('original_grey', im_grey)
plt.show()