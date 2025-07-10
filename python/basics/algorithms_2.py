import re
import copy
import random
import math

# Завдання 6_1: Ввести рядок, в якій записана сума натуральних чисел,
print("Завдання 6_1:")
userInput = input("Введите набор чисел, разделенных символом '+', для сложения: ")
inputList = re.split(r'\s*\+\s*', str(userInput));
Sum = int(0)
for item in inputList:
    if not(re.search(r'\s*[^0-9]\s*', item))and(item!=""):
        Sum += math.fabs(int(item))
print("Sum =", Sum)
print()

# Завдання 6_2: Дан список з 5 різних елементів. Використовуючи функції
# (не використовувати цикл), необхідно знайти і вивести:
# • мінімальний і максимальний елементи списку;
# • суму і середнє арифметичне;
# • другий мінімальний елемент (другий по мінімальності).
print("Завдання 6_2:")
someList = [1, 2, 3, 4, 5, 10, 9, 8, 7, 6]
print("someList =", someList)
listMax = max(someList)
listMin = min(someList)
listMinIndex = someList.index(listMin)
listMinSecond = min(copy.deepcopy(someList[0:listMinIndex] + someList[listMinIndex+1:]))
print("listMax =", listMax)
print("listMin =", listMin)
print("listMinSecond =", listMinSecond)
print()

# Завдання 6_3: Перевірити, чи є задане слово паліндромом.
# Примітка:
# • Приклади паліндромів: казак, ABBA
# • Використовувати функції.
print("Завдання 6_3:")
userInput = str(input("Введите строку для проверки палиндрома: "))
inputList = list(userInput)
inputListSize = int(len(inputList))
palindromeTrigger = True
for i in range(int(inputListSize/2)):
    if (inputList[i] != inputList[inputListSize-i-1]):
        palindromeTrigger = False
        break
if (palindromeTrigger):
    print("'", userInput, "' является палиндромом", sep="")
else:
    print("'", userInput, "' не является палиндромом", sep="")
print("")

# Завдання Python 6_4: Знайдіть в масиві все прості числа і скопіюйте їх в
# новий масив.
print("Завдання 6_4:")
def isSimpleNumber(term):
    counter = 0
    for i in range(1,term+1):
        if (term % i == 0): counter += 1
    if (counter <= 2): return True
    else: return False

userList = [1, 2, 3, 4, 5, 10, 9, 8, 7, 6]
someList = []
for item in userList:
    if isSimpleNumber(item):
        someList.append(item)
print("userList =", userList)
print("someList =", someList, "- простые числа")
print("")

# Завдання Python 6_5: Вирішити задачу пошуку середнього значення в
# списку з N елементів (вводяться в вигляді рядків). Використовувати метод
# додавання елементів списку і підсумовування елементів
print("Завдання 6_5:")
userList = []
userInput = ""
continueFlag = True
while (True):
    userInput = input("Заполнение списка: ")
    if (userInput == ""): break
    userInput = re.sub(r'([^0-9\.])|(\..*\.)', "", userInput)
    if (userInput != ""): userList.append(userInput)
Sum = 0
for item in userList:
    Sum += float(item)
Sum /= len(userList)
print("userList =", userList)
print("average =", Sum)
print()

# Завдання Python 6_6: Визначити індекси елементів масиву (списку),
# значення яких належать заданому діапазону (тобто не менше заданого мінімуму
# і не більше заданого максимуму)
# 1) Заповнити список (масив) випадковими числами.
# 2) Запросити для введення мінімум і максимум діапазону.
# 3) Знайти індекси елементів, значення яких входять в діапазон.
# Додавати знайдені індекси до нового списку.
# 4) Вивести загальне число знайдених індексів (функція len ()) і окремо
# всі індекси.
print("Завдання 6_6:")
userList = []
for i in range(20):
    userList.append(random.randint(-128, 128))
someList = []
userMin = int(input("Введите число для нижнего предела отсеивания: "))
userMax = int(input("Введите число для верхнего предела отсеивания: "))
for i in range(0, len(userList)):
    if (userList[i] >= userMin) and (userList[i] <= userMax):
        someList.append(i)
print("userList =", userList)
print("indexes of items in (",userMin,",",userMax,") range:", someList)
print("with total amount of", len(someList), "found items")
print()

# Завдання Python 6_7: Доповнити попередню програму наступним:
# Після того, як елемент з відповідним значенням доданий в новий список –
# видаляти його з вихідного списку
# * Використовувати цикл while, функцію len ()
print("Завдання 6_7:")
userList = []
for i in range(20):
    userList.append(random.randint(-128, 128))
inputList = copy.deepcopy(userList)
someList = []
userMin = int(input("Введите число для нижнего предела отсеивания: "))
userMax = int(input("Введите число для верхнего предела отсеивания: "))
position = 0
while (position < len(userList)):
    if (userList[position] >= userMin) and (userList[position] <= userMax):
        userList.pop(position)
        someList.append(position)
    position += 1
print("userList =", inputList)
print("->")
print("userList =", userList)
print("indexes of items in (",userMin,",",userMax,") range:", someList)
print("with total amount of", len(someList), "found items")
print()