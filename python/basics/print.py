# x = input("x = ")
# y = input("y = ")
# print("x = {0}; y = {1};".format(x, y))

import math

# Завдання 1.1:
# Використовуючи оператори input і print,
# виведіть значення цілих змінних
# x = 5 і y = 3 в наступних форматах:
# 3+5=?
# 3 | 5 | 8
# Z(5)=F(3)
# x=5; y=3;
# Відповідь: (5;3)
print("Задание 1.1")
ans_X = int(input("Введите значение x, целое число, x = "))
ans_Y = int(input("Введите значение y, целое число, y = "))
print(ans_X, "+", ans_Y, "=", "?")
print(ans_X, "+", ans_Y, "=", ans_X + ans_Y)
print(ans_X, "|", ans_Y, "|", ans_X + ans_Y)
print("Z(", ans_X, ")=F(", ans_Y, ")", sep="")
print("x=", ans_X, "; y=", ans_Y, ";", sep="")
print("Відповідь: (", ans_X, ";", ans_Y, ")", sep="")

# Завдання 1.2:
# Дано дві змінні. Запросити їх значення.
# Виконати основні арифметичні дії зі змінними,
# цілочисельне ділення, зведення в квадрат.
# Здійснити переклад в системи числення.
# Вивести результат.
print("\n")
print("Задание 1.2")
a = float(input("Введите переменную a, a = "))
b = float(input("Введите переменную b, b = "))
print(a, "+", b, "=", a + b, sep="")
print(a, "-", b, "=", a - b, sep="")
print(a, "*", b, "=", a * b, sep="")
print(a, "/", b, "=", a / b, sep="")
print(a, "//", b, "=", a // b, sep="")
print(a, "^2", "=", a ** 2, sep="")
print(a, "^", b, "=", a ** b, sep="")
print(a, "%", b, "=", a % b, sep="")
print("bin(", a, ")= ", bin(int(a)), "; bin(", b, ")=", bin(int(b)), sep="")
print("hex(", a, ")= ", hex(int(a)), "; hex(", b, ")=", hex(int(b)), sep="")
print("oct(", a, ")= ", oct(int(a)), "; oct(", b, ")=", oct(int(b)), sep="")

# Завдання 1.3:
# Запитується кількість годин і заробіток на годину. Розрахувати зарплату.
# Якщо працівник працював понад 40 годин, - то зарплата множиться на коефіцієнт 1,5.
# Оформити в форматі дружнього інтерфейсу.
print("\n")
print("Задание 1.3")
hours = float(input("Введите часы работы hours, hours = "))
salary = float(input("Введите почасовую оплату salary, salary = "))
hours_threshold = 40
hours_coefficient = 1.5
if hours > hours_threshold:
    payment = hours * salary * hours_coefficient
    print("Т.к. вы работали больше", hours_threshold,"часов, то ваша salary =", payment)
else:
    payment = hours * salary
    print("Ваша salary =", payment)
    
# Завдання 1.4:
print("\n")
A = float(input("Введите A, A = "))
B = float(input("Введите B, B = "))
x = float(input("Введите x, x = "))
a = float(input("Введите a, a = "))
b = float(input("Введите b, b = "))
c = float(input("Введите c, c = "))
print("x =", (0.51 * pow(x, 3) + A * B) / (1 + math.cos(0.5)) + A / (A + B) )
print("x =", (a*b/c)+(math.fabs(a-b)/math.cos(pow(a,3))) )
print("y =", 0.87*math.fabs(pow(a,2)+math.sqrt(b)*a)/(x-1+(1+b)/(1-a)) )
print("y =", math.sqrt(math.fabs(x+math.sqrt(math.fabs(pow(x,2)))/(1-2*x))) )
print("y =", pow((1+x),2)+(math.sqrt(1+pow(x,2))/pow(math.cos(x),2)) )
print("y =", 0.5*x-((a*x-b+c)*x-b)/(x-1) )