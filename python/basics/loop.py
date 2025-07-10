from random import randint

# Завдання Python 4_1: Створіть список
# цілих чисел від -20 до 30 (генерація).
print("=== Завдання 4_1:")
interger_list = [i for i in range(-20, 31)]
for i in range(len(interger_list)) :
    print( "[", interger_list[i], "] ", sep="", end="" )
print("\n")

# Завдання Python 4_2: Створіть список
# цілих чисел від -10 до 10 з кроком 2
# (генерація list).
print("=== Завдання 4_2:")
interger_list = [i for i in range(-10, 11, 2)]
for i in range(len(interger_list)) :
    print( "[", interger_list[i], "] ", sep="", end="" )
print("\n")

# Завдання Python 4_3: Створіть список з
# 20 п'ятірок (генерація).
print("=== Завдання 4_3:")
interger_list = []
iterator_temp = 1
range_temp = 5
for i in range(20):
    interger_list.append([iterator_temp + j for j in range(range_temp)])
    iterator_temp += range_temp
for i in range(len(interger_list)) :
    print("[ ",end="")
    for j in range(len(interger_list[i])) :
        print( "[", interger_list[i][j], "] ", sep="", end="" )
    print("] ")
print("\n")

# Завдання Python 4_4: Створіть список із
# сум трійок чисел від 0 до 10,
# використовуючи генератор списку
# (0 + 1 + 2, 1 + 2 + 3, ...).
print("=== Завдання 4_4:")
interger_list = [i * 3 + 3 for i in range(9)]
for i in range(len(interger_list)) :
    print( "[", interger_list[i], "] ", sep="", end="" )
print("\n")

# Завдання Python 4_5: Заповніть масив
# елементами арифметичної прогресії.
# Її перший елемент, різниця і кількість
# елементів потрібно ввести з клавіатури.
# * Формула для отримання n-го члена
# прогресії: an = a1 + (n-1) * d
print("=== Завдання 4_5:")
a1 = int(input("Введите первый элемент арифметической прогрессии: "))
d = int(input("Введите слагаемое арифметической прогрессии: "))
N = int(input("Введите число элементов арифметической прогрессии: "))
interger_list = [a1 + i * d for i in range(N+1)]
for i in range(len(interger_list)) :
    print( "[", interger_list[i], "] ", sep="", end="" )
print("\n")

# Завдання Python 4_6: Заповніть масив
# випадковими числами
# в діапазоні 20..100 і підрахуйте окремо
# число парних і непарних елементів.
print("=== Завдання 4_6:")
interger_list = [randint(20,100) for i in range(100)]
odd_count = int(0)
even_count = int(0)
for i in range(len(interger_list)) :
    if interger_list[i] % 2:
        odd_count += 1
    else:
        even_count += 1
    print( "[", interger_list[i], "] ", sep="", end="" )
print()
print( "Число нечетных элементов: ", odd_count, ", четных: ", even_count, sep="" )