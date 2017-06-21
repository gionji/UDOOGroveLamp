# use Tkinter to show a digital clock
# tested with Python24    vegaseat    10sep2006

#http://www.python-course.eu/tkinter_labels.php

import Tkinter as tk
import time
from PIL import ImageTk,Image
from ttk import Frame, Button, Style

root = tk.Tk()
root.attributes("-fullscreen", True)


image = Image.open('/home/udooer/UDOOGroveLamp/python/bgClock01.png')
# Resize
image = image.resize((800, 480), Image.ANTIALIAS)
photo_image = ImageTk.PhotoImage(image)
label = tk.Label(root, image = photo_image)
label.place(x=0, y=0, relwidth=1, relheight=1)

alarmtime = tk.Label(root, text  = "12.30am").place(relx=0.8, rely=0.1, anchor=tk.CENTER)
time = tk.Label(root, text  = "che ore sono?").place(relx=0.5, rely=0.5, anchor=tk.CENTER)
time.config(font=("Helvetica", 50))
tk.Button(root, text = "Settings").place(relx=0.1, rely=0.1, anchor=tk.CENTER)
tk.Button(root, text = "Alarm").place(relx=0.9, rely=0.1, anchor=tk.CENTER)     
        
root.mainloop(  )
