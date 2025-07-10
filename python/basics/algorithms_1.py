import random
# Завдання 2.1: Послідовно вводяться ненульові числа. Визначити суму позитивних і
# суму негативних чисел. Закінчити введення чисел при введенні 0. Для перекладу з рядка в
# ціле число, використовувати функцію int ().
input_ans = int(906)
input_list_positive = []
input_list_negative = []
while 1 :
    input_ans = float(input("Input any number: "))
    if (input_ans == 0) :
        print("The end of the input")
        break
    elif input_ans > 0 :
        input_list_positive.append(input_ans)
    else :
        input_list_negative.append(input_ans)
positive_sum = int(0)
negative_sum = int(0)
for iterator in input_list_positive :
    positive_sum += iterator
for iterator in input_list_negative :
    negative_sum += iterator
print("The sum of all of the entered numbers that are positive is", positive_sum)
print("The sum of all of the entered numbers that are negative is", negative_sum)

print()
# Завдання 2.2: За допомогою циклу роздрукувати ряд Фібоначчі: 1 1 2 3 5 8 13 21.
fib1 = 1
fib2 = 1
n = int(input("Number of elements of Fibonacci sequence is "))
i = 2
print("The 1 element is", fib1)
print("The 2 element is", fib2)
while i < n:
    i += 1
    fib_sum = fib1 + fib2
    fib1 = fib2
    fib2 = fib_sum
    print("The", i + 1,"element is", fib2)

print()
# Завдання 2.3: Скласти програму для обчислення середнього арифметичного N
# довільних чисел, що вводяться.
input_list_toaverage = []
while 1 :
    input_ans = float(input("Input any number: "))
    if (input_ans == 0) :
        print("The end of input")
        break
    input_list_toaverage.append(input_ans)
list_average = float(0)
list_size = int(0)
for iterator in input_list_toaverage :
    list_average += iterator
    list_size += 1
list_average /= list_size
print("The average of the entered numbers is", list_average)

print()
# Завдання 2.4: Виправити попереднє завдання (3) для роботи з випадковими числами.
input_list_toaverage_rand = []
input_ans = int(input("Input quantity of number to generate: "))
i = 0
random_stream = float(random.random()) * 1000000
while i < input_ans :
    random.seed(random_stream)
    random_stream = float(random.random()) * 1000000
    input_list_toaverage_rand.append(random_stream)
    i += 1
list_average = float(0)
list_size = int(0)
for iterator in input_list_toaverage_rand :
    list_average += iterator
    list_size = list_size + 1
list_average /= list_size
print("The average of the randomly generated", input_ans,"numbers is", list_average)

print()
# Завдання 2.5: Роздруковувати дні тижня з їх порядковими номерами. Крім того, поруч
# виводити вихідний чи це день або робочий. Використовувати кортеж.
days = ("monday ","tuesday ","wednesday","thursday ","friday ","saturday ","sunday ")
i = 1
for iterator in days :
    if not(i % 6) or not(i % 7) :
        print(iterator, "\tis", i, "day of the week and is a day for rest")
    else :
        print(iterator, "\tis", i, "day of the week and is a day for work")
    i += 1