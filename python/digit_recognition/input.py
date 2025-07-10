from keras.models import load_model
from keras.preprocessing.image import img_to_array
from tkinter import *
import tkinter as tk
import win32gui
from PIL import ImageGrab, ImageOps, ImageTk, Image
import numpy as np
import os
import glob


def noise(img, c):
    if c == 0:
        return img
    loc = 0
    scale = 255.0*c
    for y in range(img.height):
        for x in range(img.width):
            value = img.getpixel((x, y))
            red = (value[0] + int(np.random.normal(loc, scale)))
            green = (value[1] + int(np.random.normal(loc, scale)))
            blue = (value[2] + int(np.random.normal(loc, scale)))
            img.putpixel((x, y), (red, green, blue))
    return img


class App(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.x = self.y = 0
        self.cwd = os.getcwd()
        # Creating elements
        self.canvas = tk.Canvas(
            self, width=300, height=300, bg="white", cursor="cross")
        self.preview = tk.Canvas(
            self, width=300, height=300, bg="black")
        self.label = tk.Label(self,
                              justify="left",
                              text="...",
                              font=("Helvetica", 16))
        self.button_clear = tk.Button(
            self, text="Clear", command=self.clear_all)
        self.slider = tk.Scale(self, from_=0, to=1000,
                               length=300, orient=HORIZONTAL)
        self.model_list = self.list_h5_models()
        self.model_selected = tk.StringVar(self)
        self.model_selected.set(self.model_list[0])
        self.model_dropdown = tk.OptionMenu(self,
                                            self.model_selected,
                                            *self.model_list,
                                            command=self.select_h5_model)
        self.canvas.grid(row=0, column=0, sticky=W)
        self.label.grid(row=0, column=1, pady=2, padx=2)
        self.preview.grid(row=0, column=2, sticky=W)
        self.button_clear.grid(row=1, column=0)
        self.slider.grid(row=1, column=1, columnspan=2, sticky=E)
        self.model_dropdown.grid(row=2, column=0, columnspan=3)
        self.canvas.bind("<B1-Motion>", self.draw_lines)
        self.canvas.bind("<ButtonRelease-1>", self.auto_classify_adapter)
        self.slider.bind("<ButtonRelease-1>", self.update_noise_scale)
        # initialize available model
        self.reload_model()
        self.noise_scale = 0.0
        self.pen_radius = 8

    def clear_all(self):
        self.canvas.delete("all")

    def reload_model(self):
        self.model = load_model(f'{self.cwd}\\{self.model_selected.get()}')

    def list_h5_models(self):
        found = glob.glob(f'{self.cwd}\\*.h5')
        return [os.path.split(path)[-1] for path in found]

    def select_h5_model(self, event):
        self.model_list = self.list_h5_models()
        self.model_dropdown.text = self.model_selected.get()
        self.reload_model()

    def classify_handwriting(self):
        HWND = self.canvas.winfo_id()  # get the handle of the canvas
        rect = win32gui.GetWindowRect(HWND)  # get the coordinate of the canvas
        img = ImageGrab.grab(rect)
        # resize for input, make grayscale, invert to match training data
        img = img.resize((28, 28))
        img = noise(img, self.noise_scale / 1000)  # add noise
        img = ImageOps.invert(img)
        img = img.convert("L")
        # preview NN input image
        preview = ImageTk.PhotoImage(img.resize(
            (self.preview.winfo_width(), self.preview.winfo_height()),
            Image.NEAREST))
        self.preview.create_image(0, 0, anchor=NW, image=preview)
        self.preview.image = preview
        # reshaping to support the model input and normalizing
        img = img_to_array(img)
        img = img.reshape(1, 28, 28, 1)
        img = img.astype('float32')
        img = img / 255.0
        # predicting the class
        res = self.model.predict([img])
        res_string = ""
        for i in range(len(res[0])):
            res_string += str(i)+" : " + str(int(res[0][i]*100))+"%\n"
        self.label.configure(text=res_string)

    def draw_lines(self, event):
        self.x = event.x
        self.y = event.y
        self.canvas.create_oval(
            self.x - self.pen_radius,
            self.y - self.pen_radius,
            self.x + self.pen_radius,
            self.y + self.pen_radius,
            fill="black")

    def auto_classify_adapter(self, event):
        self.classify_handwriting()

    def update_noise_scale(self, event):
        self.noise_scale = self.slider.get()
        self.classify_handwriting()


app = App()

mainloop()
