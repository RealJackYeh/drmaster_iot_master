import RPi.GPIO as GPIO
import time
# GPIO腳位定義
in1 = 17
in2 = 18 
in3 = 27 
in4 = 22
step_sleep = 0.002 # 每步之間的時間ms，值愈大轉速愈慢
 # 轉一圈需要的步數（5.625*(1/64) per step, 4096 steps is 360°）
step_count = 4096 
 
direction = True #控制方向，True為逆時針，False為順時針
# Half-step mode激磁表，共有8步，見表2-8-1 
step_sequence = [[1,0,0,1],
                 [1,0,0,0],
                 [1,1,0,0],
                 [0,1,0,0],
                 [0,1,1,0],
                 [0,0,1,0],
                 [0,0,1,1],
                 [0,0,0,1]]
 
# 樹莓派腳位設定
GPIO.setmode( GPIO.BCM )
GPIO.setup( in1, GPIO.OUT )
GPIO.setup( in2, GPIO.OUT )
GPIO.setup( in3, GPIO.OUT )
GPIO.setup( in4, GPIO.OUT )
 
# 樹莓派腳位初始化
GPIO.output( in1, GPIO.LOW )
GPIO.output( in2, GPIO.LOW )
GPIO.output( in3, GPIO.LOW )
GPIO.output( in4, GPIO.LOW )
 
 
motor_pins = [in1,in2,in3,in4] #定義馬達腳位陣列
motor_step_counter = 0 #目前所在步數
 
 
def cleanup(): #清除GPIO腳位定義副程式
    GPIO.output( in1, GPIO.LOW )
    GPIO.output( in2, GPIO.LOW )
    GPIO.output( in3, GPIO.LOW )
    GPIO.output( in4, GPIO.LOW )
    GPIO.cleanup()
 
 
#控制主程序
i = 0
for i in range(step_count): #完整轉一圈
    # 針對每一個控制腳位分別輸出訊號
    for pin in range(0, len(motor_pins)):
        #根據激磁表，不同腳位輸出不同訊號
        GPIO.output( motor_pins[pin], step_sequence[motor_step_counter][pin] )
    #正反轉查表方向不同
    if direction==True:
        motor_step_counter = (motor_step_counter - 1) % 8
    elif direction==False:
        motor_step_counter = (motor_step_counter + 1) % 8
    time.sleep( step_sleep ) # 每步之間的延遲時間
 
cleanup()
exit(0)