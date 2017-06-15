# use Tkinter to show a digital clock
# tested with Python24    vegaseat    10sep2006

#http://www.python-course.eu/tkinter_labels.php

from Tkinter import *
import time
from PIL import Image

root = Tk()
root.attributes("-fullscreen", True)
time1 = ''

image= Image.open("eyesbg.jpg")
backImg = PhotoImage(image)
backImgLabel = Label(root, image=backImg)
backImgLabel.place(x=0,y=0, relwidth=1, relheight=1)

clock = Label(root, font=('verdana', 120, 'bold'), fg='white')
clock.pack(fill=BOTH, expand=1)
def tick():
    global time1
    # get the current local time from the PC
    time2 = time.strftime('%H:%M:%S')
    # if time string has changed, update it
    if time2 != time1:
        time1 = time2
        clock.config(text=time2)
    # calls itself every 200 milliseconds
    # to update the time display as needed
    # could use >200 ms, but display gets jerky
    clock.after(200, tick)
tick()
root.mainloop(  )