from lib2to3.pytree import type_repr
from ntpath import join
from time import sleep
from typing import List
import cv2
import serial
from cvzone.HandTrackingModule import *
import cvzone
port = serial.Serial("COM4", 9600,bytesize=8, parity=serial.PARITY_EVEN, stopbits=1)


detector=HandDetector(detectionCon=0.75,maxHands=2)
cap=cv2.VideoCapture(0)

while True:
    sucess,img = cap.read()
    hands,img = detector.findHands(img)
    f1f = "$"
    
    if hands:
        hand1=hands[0]
        finger1=detector.fingersUp(hand1) #Esto es una list
        
        if len(hands) == 2:
            hand2=hands[1]
            finger2 = detector.fingersUp(hand2)

            #creamos estas variables (b) y (c) que son tipo string para transformar la list a un string
            b =''.join(str(x) for x in finger1)
            c =''.join(str(o) for o in finger2)
            f1f = f1f+b+c
            print(f1f)
            port.write(str.encode(f1f))
           
    cv2.imshow("HAND",img)
    if cv2.waitKey(1)& 0xFF==ord("c"):
        break