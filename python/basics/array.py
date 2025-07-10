from prettytable import PrettyTable
import numpy
import math
import random

## Завдання Python 8_0: Отримано значення температури повітря за 4 дні з
## трьох метеостанцій, розташованих в різних регіонах країни:
## Номер станції 1-й день 2-й день 3-й день 4-й день
## 1 -8 -14 -19 -18
## 2 25 28 26 20
## 3 11 18 20 25
## Тобто запис свідчень у двовимірному масиві виглядала б так:
## t[1,1]:=-8; t[1,2]:=-14; t[1,3]:=-19; t[1,4]:=-18;
## t[2,1]:=25; t[2,2]:=28; t[2,3]:=26; t[2,4]:=20;
## t[3,1]:=11; t[3,2]:=18; t[3,3]:=20; t[3,4]:=25;
## 1) Роздрукувати температуру на 2-й метеостанції за 4-й день і на 3-й
## метеостанції за 1-й день.
## 2) Роздрукувати показання термометрів всіх метеостанцій за 2-й день.
## 3) Визначити середню температуру на 3-й метеостанції.
## 4) Роздрукувати, в які дні і на яких метеостанціях температура була в
## діапазоні 24-26 градусів тепла.
arr1 = []
arr1.append([])
arr1[0].append(-8)
arr1[0].append(-14)
arr1[0].append(-19)
arr1[0].append(-18)
arr1.append([])
arr1[1].append(25)
arr1[1].append(28)
arr1[1].append(26)
arr1[1].append(20)
arr1.append([])
arr1[2].append(11)
arr1[2].append(18)
arr1[2].append(20)
arr1[2].append(25)
print("=== Завдання 8_0")
print("Роздрукувати температуру на 2-й метеостанції за 4-й день і на 3-й метеостанції за 1-й день: ")
print("arr1[1][3]:", arr1[1][3])
print("arr1[2][0]:", arr1[2][0])
print("Роздрукувати показання термометрів всіх метеостанцій за 2-й день: ")
tableString = ""
for i in range(len(arr1)):
    tableString += "На станції " + str(i+1) + " за 2й день температура " + str(arr1[i][1]) + "градусів\n"
print(tableString)
print("Визначити середню температуру на 3-й метеостанції: ")
num = 0
for i in range(len(arr1[2])):
    num += arr1[2][i]
    print("День", i+1, "," , arr1[2][i] , "градусів")
num /= len(arr1[2])
print("Середня температура", num, "градусів")
print("Роздрукувати, в які дні і на яких метеостанціях температура була в діапазоні 24-26 радусів тепла: ")
for i in range(len(arr1)):
    for j in range(len(arr1[i])):
        if (arr1[i][j] >= 24)and(arr1[i][j] <= 26):
            print("Станція", i+1, "," , j+1, "день ,", arr1[i][j] , "градусів")
ptable = PrettyTable()
arr1copy = arr1[::]
ptable.field_names =["№", "1 день", "2 день", "3-й день", "4-й день"]
for i in range(len(arr1copy)):
    arr1copy[i].insert(0, i+1)
    ptable.add_row(arr1copy[i])
print(ptable)
print()

## Завдання Python 8_1: Написати програму пошуку мінімального та
## максимального елементів матриці і їх індексів.
def minIndexesMatrix(data = [[]]):
    tempItem = (2**(8*4))
    tempIndexI = 0
    tempIndexJ = 0
    for i in range(len(data)):
        for j in range(len(data[i])):
            if (tempItem > data[i][j]):
                tempItem = data[i][j]
                tempIndexI = i
                tempIndexJ = j
    return tempIndexI, tempIndexJ

def maxIndexesMatrix(data):
    tempItem = -(2**(8*4))
    for i in range(len(data)):
        for j in range(len(data[i])):
            if (tempItem < data[i][j]):
                tempItem = data[i][j]
                tempIndexI = i
                tempIndexJ = j
    return tempIndexI, tempIndexJ

print("=== Завдання 8_1")
num1, num2 = minIndexesMatrix(arr1)
print("minIndexesMatrix(arr1):", minIndexesMatrix(arr1))
print("arr1[minIndexesMatrix(arr1)]:", arr1[num1][num2])
num1, num2 = maxIndexesMatrix(arr1)
print("maxIndexesMatrix(arr1):", maxIndexesMatrix(arr1))
print("arr1[maxIndexesMatrix(arr1)]:", arr1[num1][num2])
print()

## Завдання Python 8_2: Написати програму, що виводить на екран рядок
## матриці, сума елементів якої максимальна.
def maxIndex(data):
    tempItem = -(2**(8*4))
    tempIndex = 0
    for i in range(len(data)):
        if (tempItem < data[i]):
            tempItem = data[i]
            tempIndex = i
    return tempIndex

def printMaxRowMatrix(data = [[]]):
    tempSum = []
    for i in range(len(data)):
        tempSum.append(sum(data[i]))
    if len(tempSum):
        print("maxRowMatrix:", data[maxIndex(tempSum)])
    else:
        print("maxRowMatrix: Входные данные имеют нулевой размер")

print("=== Завдання 8_2")
print("printMaxRowMatrix(arr1):")
printMaxRowMatrix(arr1)
print()

## Завдання Python 8_3: Скласти програму, що дозволяє за допомогою
## датчика випадкових чисел сформувати матрицю розмірністю N.
## Визначити:
##  мінімальний елемент, що лежить нижче побічної діагоналі;
##  твір ненульових елементів останнього рядка.
def getMatrixRandom(size):
    toreturn = []
    for i in range(size):
        toreturn.append([])
        for j in range(size):
            toreturn[i].append(round(random.random()*100))
    return toreturn

def maxUnderSideDiagonal(data):
    tempItem = -(2**(8*4))
    for i in range(math.ceil(len(data)/2),len(data)):
        for j in range(math.ceil(len(data[i])/2),len(data[i])):
            if (tempItem < data[i][j]):
                tempItem = data[i][j]
    return tempItem

def lastRowMultMatrix(data):
    tempMult = 1
    sizeIndexed = len(data) - 1
    for i in range(len(data) - 1):
        if (data[sizeIndexed][i] != 0):
            tempMult *= data[sizeIndexed][i]
    return tempMult

print("=== Завдання 8_3")
print("getMatrixRandom(5):")
matrix1 = getMatrixRandom(5)
print(numpy.matrix(matrix1))
print("maxUnderSideDiagonal(matrix1):", maxUnderSideDiagonal(matrix1))
print("lastRowMultMatrix(matrix1):", lastRowMultMatrix(matrix1))
print()