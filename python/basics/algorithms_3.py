import random

# Завдання Python 7_1: Дан масив. Необхідно підтвердити,
# що в масиві є числа, кратні трьом.
print("Завдання 7_1")
arr1 = [random.randint(1,30) for i in range(25)]
userList = []
for i in range(len(arr1)):
    if(arr1[i]%3==0): userList.append(arr1[i])
print("arr1 =", arr1)
if(len(userList)):
    print("Найдены числа кратные трём:", userList)
else:
    print("Числа кратные трём не найдены")
print()

# Завдання Python 7_2: Заповніть масив випадковими числами
# в діапазоні 0..4 і виведіть на екран номери всіх
# елементів, рівних значенням X (воно вводиться з клавіатури).
print("Завдання 7_2")
arr1 = [random.randint(0,4) for i in range(25)]
userList = []
print("arr1 =", arr1)
userInput = int(input("Введите искомое значение: "))
for i in range(len(arr1)):
    if(arr1[i]==userInput): userList.append(i)
if(len(userList)):
    print("Найдены искомые числа по индексам:", userList)
else:
    print("Искомые числа не найдены")
print()

# Завдання Python 7_3: Заповніть масив випадковими числами.
# Знайдіть номери першого мінімального і останнього
# максимального елемента масиву.
def monotoneDataEndIndex(data = 0, fromBegin = True, isIncreasing = True):
    dataLenght = len(data)
    if (isIncreasing):
        if (fromBegin):
            index = 0
            while (index < dataLenght - 2):
                if (data[index]>data[index+1]): break
                index += 1
        else:
            index = dataLenght - 1
            while (index > 0):
                if (data[index]>data[index-1]): break
                index -= 1
    else:
        if (fromBegin):
            index = 0
            while (index < dataLenght - 2):
                if (data[index]<data[index+1]): break
                index += 1
        else:
            index = dataLenght - 1
            while (index > 0):
                if (data[index]<data[index-1]): break
                index -= 1
    return index

print("Завдання 7_3")
arr1 = [random.randint(0,4) for i in range(10)]
print("arr1 =", arr1)
MinBeginIndex = 0
MinEndIndex = monotoneDataEndIndex(arr1[::], True, True)
MaxBeginIndex = len(arr1)
MaxEndIndex = monotoneDataEndIndex(arr1[::], False, True)
MinFromBegin = arr1[0]
MaxFromEnd = arr1[MaxEndIndex]
print("В последовательности", arr1[MinBeginIndex : MinEndIndex+1:], "элемент",
      MinFromBegin,
      "минимальный")
print("В последовательности", arr1[MaxEndIndex : MaxBeginIndex:], "элемент",
      MaxFromEnd,
      "максимальный")
print()

# Завдання Python 7_4: Необхідно написати програму, в якій
# сортування виконується «методом каменю» - самий «важкий»
# елемент опускається в кінець масиву.
def bubbleSort(data):
    print(data)
    continueFlag = True
    while (continueFlag):
        continueFlag = False
        for i in range(len(data) - 1):
            if(data[i] > data[i+1]):
                continueFlag = True
                data[i],data[i+1] = data[i+1],data[i]
                print(data)

def rockSort(data):
    print(data)
    i = 0
    continueFlag = True
    while (continueFlag):
        continueFlag = False
        if (i == len(data)):
            i = 0
        for j in range(len(data) - i - 1):
            if (data[j] > data[j+1]):
                continueFlag = True
                data[j],data[j+1] = data[j+1],data[j]
                print(data)
        i += 1

print("Завдання 7_4")
arr1 = [random.randint(0, 4) for i in range(6)]
print("=== arr1", arr1)
print("=== bubbleSort(arr1)")
bubbleSort(arr1[::])
print("=== rockSort(arr1)")
rockSort(arr1[::])
print()

# Завдання Python 7_5: Необхідно написати програму, яка
# сортує масив (швидкої сортуванням) по зростанню першої
# цифри числа.
def partition(data, low, high):
    center = data[(low + high) // 2]
    i = low - 1
    j = high + 1
    while True:
        i += 1
        while (data[i] < center): i += 1
        j -= 1
        while (data[j] > center): j -= 1
        if (i >= j): return j
        else:
            data[i],data[j] = data[j],data[i]
            print(data)

def quickSort(data, left, right):
    if left < right:
        split_index = partition(data, left, right)
        quickSort(data, left, split_index)
        quickSort(data, split_index + 1, right)

def _partition(data, low, high):
    center = data[(low + high) // 2]
    i = low - 1
    j = high + 1
    while True:
        i += 1
        while (data[i][0] < center[0]): i += 1
        j -= 1
        while (data[j][0] > center[0]): j -= 1
        if (i >= j): return j
        else:
            data[i],data[j] = data[j],data[i]
            print(data)

def _quickSort(data, left, right):
    if left < right:
        split_index = _partition(data, left, right)
        _quickSort(data, left, split_index)
        _quickSort(data, split_index + 1, right)

print("Завдання 7_5")
arr1 = [random.randint(10, 99) for i in range(6)]
arr4 = []
for i in range(len(arr1)):
    arr4.append(str(arr1[i]))
print("=== arr4", arr4)
print("=== quickSort(arr4)")
_quickSort(arr4, 0, len(arr4) - 1)
print()

# Завдання Python 7_6: Напишіть програму, яка, не змінюючи
# заданий масив, виводить номера його елементів в порядку
# зростання. Використовувати допоміжний масив номерів.
def minimalNonSubtracted(data, subtraction):
    index = -1
    temp = 2**(8*4)
    for i in range(len(data)):
        if(not(i in subtraction) and (temp > data[i])):
            temp = data[i]
            index = i
    return index

def increasingSequenceIndexes(data):
    subtraction = []
    while (len(subtraction) < len(data)):
        subtraction.append(minimalNonSubtracted(data, subtraction))
    return subtraction

print("Завдання 7_6")
arr1 = [random.randint(0,100) for i in range(10)]
arr2 = increasingSequenceIndexes(arr1)
userList = []
for i in range(len(arr2)):
    userList.append(arr1[arr2[i]])
print("=== arr1", arr1)
print("=== increasingSequenceIndexes(arr1)")
print(arr2)
print("=== arr1[increasingSequenceIndexes(arr1)]")
print(userList)
print()

# Завдання Python 7_7: Напишіть програму, яка сортує масив
# і знаходить кількість різних чисел в ньому. Чи не
# використовувати вбудовані функції.
def getCountDictionary(data):
    dictionary = {}
    for i in range(len(data)):
        if (dictionary.get(data[i])==None):
            dictionary[data[i]] = 1
        else:
            dictionary[data[i]] += 1
    return dictionary

print("Завдання 7_7")
arr1 = [random.randint(0,9) for i in range(6)]
print("=== quickSort(arr1)")
quickSort(arr1, 0, len(arr1)-1)
dictionary = getCountDictionary(arr1)
print("=== unique")
arr2 = []
for key in dictionary:
    if (dictionary[key] == 1):
        arr2.append(key);
print(arr2)
print("=== repeat")
arr2 = []
for key in dictionary:
    if (dictionary[key] > 1):
        arr2.append(key);
print(arr2)
print("=== dictionary", dictionary)
print()

# Завдання Python 7_8: Дан масив. Назвемо серією групу
# поспіль однакових елементів, а довжиною серії - кількість
# цих елементів. Сформувати два нових масиву, в один з них
# записувати# №довжини всіх серій, а в другій - значення
# елементів, що утворюють ці серії.
def arraySeriesIncreaseCounter(what, count, dataKeys, dataValues):
    dataKeys.append(what)
    dataValues.append(count)

def arraySeriesCounter(data, dataKeys, dataValues):
    itemCurrent = 0
    itemNext = 0
    counter = 0
    for i in range(len(data)-1):
        itemCurrent = data[i]
        itemNext = data[i+1]
        counter += 1
        if (itemCurrent != itemNext):
            arraySeriesIncreaseCounter(itemCurrent, counter, dataKeys, dataValues)
            counter = 0
    if (len(data) >= 2) and (data[-2] != data[-1]):
        arraySeriesIncreaseCounter(data[-1], 1, dataKeys, dataValues)
    if (len(data) == 1):
        arraySeriesIncreaseCounter(data[0], 1, dataKeys, dataValues)

print("Завдання 7_8")
arr1 = [random.randint(0,1) for i in range(10)]
arr2 = []
arr3 = []
arraySeriesCounter(arr1, arr2, arr3)
print("=== arr1", arr1)
print("=== arr2: keys, arr3: values")
for i in range(len(arr2)):
    print("key:", arr2[i], ", value:", arr3[i])
print()

# Завдання Python 7_9: Напишіть варіант методу бульбашки,
# який закінчує роботу, якщо на черговому кроці зовнішнього
# циклу не було перестановок. Чи не використовувати вбудовані
# функції.
print("Завдання 7_9")
arr1 = [random.randint(0, 9) for i in range(5)]
print("=== arr1", arr1)
print("=== bubbleSort(arr1)")
bubbleSort(arr1[::])
print()

# Завдання Python 7_10: Напишіть програму, яка сортує масив,
# а потім знаходить максимальне з чисел, що зустрічаються в
# масиві кілька разів. Чи не використовувати вбудовані функції.
def maxIndex(data):
    tempItem = -(2**(8*4))
    tempIndex = 0
    for i in range(len(data)):
        if (tempItem < data[i]):
            tempItem = data[i]
            tempIndex = i
    return tempIndex

def maxItem(data):
    tempItem = -(2**(8*4))
    for i in range(len(data)):
        if (tempItem < data[i]):
            tempItem = data[i]
    return tempItem

print("Завдання 7_10")
arr1 = [random.randint(0,4) for i in range(6)]
arr2 = []
arr3 = []
quickSort(arr1, 0, len(arr1)-1)
arraySeriesCounter(arr1, arr2, arr3)
print("=== arr1", arr1)
soughtItem = maxItem(arr3);
for i in range(len(arr3)):
    if (arr3[i] == soughtItem):
        print("=== Длина серии:", arr3[i], ", элемент:", arr2[i])
print("=== arr2: keys, arr3: values")
for i in range(len(arr2)):
    print("key:", arr2[i], ", value:", arr3[i])
print()