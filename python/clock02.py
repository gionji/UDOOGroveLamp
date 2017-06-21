# use Tkinter to show a digital clock
# tested with Python24    vegaseat    10sep2006

#http://www.python-course.eu/tkinter_labels.php

import Tkinter as tk
import time
from PIL import ImageTk,Image

root = tk.Tk()
root.attributes("-fullscreen", True)

image = Image.open('/home/udooer/UDOOGroveLamp/python/bgClock01.png')

# Resize
image = image.resize((800, 480), Image.ANTIALIAS)

photo_image = ImageTk.PhotoImage(image)
label = tk.Label(root, image = photo_image)
label.pack()

root.mainloop(  )
