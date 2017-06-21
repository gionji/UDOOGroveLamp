# use Tkinter to show a digital clock
# tested with Python24    vegaseat    10sep2006

#http://www.python-course.eu/tkinter_labels.php

import Tkinter as tk
import time
from PIL import ImageTk,Image
from ttk import Frame, Button, Style

root = tk.Tk()
root.attributes("-fullscreen", True)

canvas = tk.Canvas(root, width=800, height=480)
canvas.pack()

image1 = Image.open('/home/udooer/UDOOGroveLamp/python/bgClock01.png')
tk_img = ImageTk.PhotoImage(image1)
canvas.create_image(400, 240, image=tk_img)

quit_button  = tk.Button(root, text = "Quit", command = root.quit, anchor = 'w',      width = 10, activebackground = "#33B5E5")
alarm_button = tk.Button(root, text = "Set Alarm", command = root.quit, anchor = 'w', width = 10, activebackground = "#33B5E5")
 
                    
window = canvas.create_window(10, 10, anchor='nw', window=quit_button) 

root.mainloop(  )
