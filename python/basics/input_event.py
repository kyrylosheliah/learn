import queue
from threading import Thread, active_count
from turtle import Turtle, Screen
from pynput import keyboard

def moveUp(turtle, distance):
    graphics.put((turtle.forward, distance))
def moveRight(turtle, angle):
    graphics.put((turtle.right, angle))
def moveLeft(turtle, angle):
    graphics.put((turtle.left, angle))
def moveDown(turtle, distance):
    graphics.put((turtle.back, distance))

screen = Screen()
screen.delay(0)
screen.title("TRTL GOGOGOGO")
screen.setup(800, 800)
screen.bgcolor("white")
graphics = queue.Queue(1) # size = number of hardware threads you have - 1
speed = 5

def process_queue():
    while not graphics.empty():
        action, argument = graphics.get()
        action(argument)
    if active_count() > 1:
        screen.ontimer(process_queue, 100)

def on_press(key):
    global turtle1
    global speed
    print(">> " + format(key))
    if key == keyboard.Key.up:
        moveUp(turtle1, speed)
    elif key == keyboard.Key.right:
        moveRight(turtle1, speed)
    elif key == keyboard.Key.left:
        moveLeft(turtle1, speed)
    elif key == keyboard.Key.down:
        moveDown(turtle1, speed)
    elif key == keyboard.Key.page_up:
        speed += 1
    elif key == keyboard.Key.page_down:
        speed -= 1
    elif key == keyboard.Key.esc:
        return False

def on_release(key):
    print("<< " + format(key))

turtle1 = Turtle('turtle')
turtle1.color('black')
turtle1.pensize(3)
turtle1.penup()
turtle1.goto(0, 0)
turtle1.pendown()

listener = keyboard.Listener(on_press=on_press, on_release=on_release)

thread1 = Thread(target=listener.start)
thread1.daemon = True # thread dies when main thread (only non-daemon thread) exits.
thread1.start()

def square():
    trtl = Turtle('turtle')
    trtl.color('red')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(-380, 380)
    trtl.pendown()
    trtl.forward(50)
    trtl.right(90)
    trtl.forward(50)
    trtl.right(90)
    trtl.forward(50)
    trtl.right(90)
    trtl.forward(50)

def fiveCircles():
    trtl = Turtle('turtle')
    trtl.color('green')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(0, 380)
    trtl.pendown()
    for i in range(5,1,-1):
        trtl.penup()
        trtl.goto(0, 380-((5-i)*50))
        trtl.pendown()
        for j in range(360):
            trtl.forward(i)
            trtl.right(1)

def snowflake():
    trtl = Turtle('turtle')
    trtl.color('blue')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(300, 300)
    trtl.pendown()
    for i in range(12):
        trtl.forward(100)
        trtl.back(100)
        trtl.right(30)

def squareSpiral():
    trtl = Turtle('turtle')
    trtl.color('red')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(-380, 100)
    trtl.pendown()
    for i in range(200,1,-4):
        trtl.forward(i)
        trtl.right(90)

def star():
    trtl = Turtle('turtle')
    trtl.color('green')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(-100, 120)
    trtl.pendown()
    for i in range(21):
        trtl.forward(200)
        trtl.right(170)

def moth():
    trtl = Turtle('turtle')
    trtl.color('blue')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(0, 0)
    trtl.pendown()
    for i in range(5,1,-1):
        for j in range(360):
            trtl.forward(i)
            trtl.left(1)
        for j in range(360):
            trtl.forward(i)
            trtl.right(1)

def pentagonA():
    trtl = Turtle('turtle')
    trtl.color('red')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(0, 0)
    trtl.pendown()
    for j in range(3):
        trtl.left(60)
        for i in range(4):
            trtl.forward(100)
            trtl.right(60)
        trtl.left(60)
        for i in range(4):
            trtl.forward(100)
            trtl.left(60)

def pentagonB():
    trtl = Turtle('turtle')
    trtl.color('red')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(0, 0)
    trtl.pendown()
    for j in range(3):
        trtl.left(60)
        for i in range(4):
            trtl.forward(100)
            trtl.right(60)
        trtl.left(60)
        trtl.left(60)
        for i in range(4):
            trtl.forward(100)
            trtl.left(60)
        trtl.left(60)

def pentagonC():
    trtl = Turtle('turtle')
    trtl.color('red')
    trtl.pensize(3)
    trtl.penup()
    trtl.goto(0, 0)
    trtl.pendown()
    for j in range(3):
        trtl.left(60)
        for i in range(4):
            trtl.forward(100)
            trtl.right(60)
        trtl.left(60)
        trtl.left(60)
        for i in range(4):
            trtl.forward(100)
            trtl.left(60)

square()
fiveCircles()
snowflake()
squareSpiral()
star()
moth()
#pentagonC()

process_queue()

screen.exitonclick()