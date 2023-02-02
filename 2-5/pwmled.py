#引入RPi.GPIO函式庫
import RPi.GPIO as GPIO
#引入time函式庫,作延時用
import time
count = 0 #計數器
ledPin = 21 #GPIO21腳位
GPIO.setmode(GPIO.BCM) #腳位編號方式設成BCM
GPIO.setwarnings(False) #若所使用的腳位設定沒有被清除，不顯示警告訊息
GPIO.setup(ledPin, GPIO.OUT)  #GPIO21 當輸出腳位 
pwmLed = GPIO.PWM(ledPin, 1000) #將GPIO21輸出類型設成PWM型式，載波頻率設成1kHz
pwmLed.start(0) #PWM初始輸出duty為0
try:
    while(1):    #無限迴圈
        if count < 100:
            count = count + 1    
            pwmLed.ChangeDutyCycle(count) #更新PWM輸出duty
            time.sleep(0.01)   #延時0.01秒
        if count == 100:    #若計數器數到100，則重置為零
            count = 0
            pwmLed.ChangeDutyCycle(count) #更新PWM輸出duty
            time.sleep(0.1) #延時0.1秒
except KeyboardInterrupt:   #若按下CTRL＋C則清除腳位設定，停止並離開程式
    pwmLed.stop()
    GPIO.cleanup()
    print("程式結束！")