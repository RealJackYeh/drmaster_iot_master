import cv2
cap = cv2.VideoCapture(0)  # 打開攝影機
while(True):
    ret, frame = cap.read() # 讀取攝影機影像
    im_grey = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) # 灰階影像
    cv2.imshow('im_grey', im_grey)
    if cv2.waitKey(1) == ord('q'):
        out = cv2.imwrite('im_grey.jpg', im_grey)
        break
cap.release()
cv2.destroyAllWindows()