# use Tkinter to show a digital clock
# tested with Python24    vegaseat    10sep2006

#http://www.python-course.eu/tkinter_labels.php

import Tkinter as tk
import time
from PIL import ImageTk,Image
from ttk import Frame, Button, Style

root = tk.Tk()
root.attributes("-fullscreen", True)
time1 = ''

image = Image.open('/home/udooer/UDOOGroveLamp/python/bgClock01.png')
# Resize
image = image.resize((800, 480), Image.ANTIALIAS)
photo_image = ImageTk.PhotoImage(image)
label = tk.Label(root, image = photo_image)
label.place(x=0, y=0, relwidth=1, relheight=1)

alarmtime = tk.Label(root, text  = "12.30am", font=('verdana', 30, 'bold'), bg='#39c2c6', fg="white")
alarmtime.place(relx=0.75, rely=0.1, anchor=tk.CENTER)
clock = tk.Label(root, text  = "12.32", font=('verdana', 120, 'bold'), bg='#39c2c6', fg="white")
clock.place(relx=0.5, rely=0.5, anchor=tk.CENTER)

tk.Button(root, text = "Settings").place(relx=0.1, rely=0.1, anchor=tk.CENTER)
tk.Button(root, text = "Alarm").place(relx=0.9, rely=0.1, anchor=tk.CENTER)     
      
def tick():
    global time1
    # get the current local time from the PC
    time2 = time.strftime('%H:%M')
    # if time string has changed, update it
    if time2 != time1:
        time1 = time2
        clock.config(text=time2)
    clock.after(200, tick)
tick()      
        
root.mainloop(  )
