# Завдання Python 5_1: Вийміть з рядка наступні зрізи:
# - перші вісім символів;
# - чотири символи з центру рядка;
# - п'ять символів з кінця рядка.

print("Завдання Python 5_1:")
Data1 = "1234567890"
Data1_size = int(len(Data1));
Slice1 = Data1[:8]
Slice2 = Data1[int(Data1_size/2-2):int(Data1_size/2+2)]
Slice3 = Data1[-5:]
print("Data1:", Data1)
print("Data1[:8]:", Slice2)
print("Data1[len()/2-2:len()/2+2]:", Slice3)
print("Data1[-4:]:", Slice1)
print()

# Завдання Python 5_2: Дана рядок довжиною N.
# Вивести символи рядка в зворотному порядку.
# (Не використовувати цикл).
print("Завдання Python 5_2:")
Data2 = ""
for iterator in reversed(Data1) :
    Data2 += iterator
Data3 = Data1[::-1]
print("reversed(Data1):", Data2)
print("Data1[::-1]:", Data3)
print()

# Завдання Python 5_3: Дана рядок довжиною N (N - парне число).
# Вивести символи з парними номерами в порядку зростання їх номерів:
# А2, А4, А6, ... аn
# Умовний оператор не використовувати.
print("Завдання Python 5_3:")
Data4 = ""
for iterator in Data1 :
    if int(iterator) % 2 == 0 :
        Data4 += iterator
Data5 = Data1[1::2]
print("Data1[i] % 2 == 0:", Data4)
print("Data1[1::2]:", Data5)
print()

# Завдання Python 5_4: Дана рядок довжиною N. Вивести спочатку символи
# з парними номерами (в порядку зростання номерів), а потім - символи
# з непарними номерами (також в порядку зростання номерів):
# А2, А4, А6, ... а1, а3, а5 ...
# Умовний оператор не використовувати.
print("Завдання Python 5_4:")
Data6 = Data1[2::2]
Data7 = Data1[1::2]
print("Data1[i] % 2 == 0:", Data6)
print("Data1[i] % 2 == 1:", Data7)
print()

# Завдання Python 5_5: Перетворити дату в «комп'ютерному» поданні
# (системну дату: 2016-03-26) в «російський» формат,
# т. Е. День / місяць / рік (наприклад, 26/03/2016).
# Відомо, що на рік виділено завжди 4 цифри, а на день і місяць -
# завжди 2 цифри.
print("Завдання Python 5_5:")
userInputDay = input("Введите номер дня месяца: ")
userInputMonth = input("Введите номер месяца: ")
userInputYear = input("Введите номер года: ")
Data8 = userInputDay + "-" + userInputMonth + "-" + userInputYear
Data9 = Data8.split("-")
Data10 = Data9[0]
for i in range(1, len(Data9)) :
    Data10 += "/" + Data9[i]
print("Вы ввели дату:", Data8)
print("Или же:", Data10)
print()

# Завдання Python 5_6: Ввести адресу файлу і «розібрати» його на частини,
# розділені знаком "/". Кожну частину вивести в окремому рядку.
print("Завдання Python 5_6:")
userInputPath = input("Введите местоположение файла (напр. с:/programs/data.png): ")
Data11 = userInputPath.split("/")
for iterator in Data11 :
    print(iterator)
print()

# Завдання Python 5_7: Ввести рядок, в якій записана сума натуральних чисел,
# наприклад, '1 + 25 + 3'. Обчисліть цей вислів. Використовувати рядкові
# функції мови.
print("Завдання Python 5_7:")
userInputSum = input("Введите числа для сложения (напр. 1 + 25 + 3): ")
Data12 = userInputSum.split("+")
Sum = 0
for iterator in Data12 :
    Sum += int(iterator)
print("Сумма:", Sum)
print()

# Завдання Python 5_8: Визначити, чи є введена рядок паліндромом
# («перевертнем») типу ABBA, kazak тощо.
print("Завдання Python 5_8:")
userInputPalindrome = str(input("Ввод для проверки палиндрома: "))
PalSize = int(len(userInputPalindrome))
PalHalfSize = int(PalSize / 2)
isPalindrome = True
for i in range(0, PalHalfSize) :
    if (userInputPalindrome[i] != userInputPalindrome[PalSize-i-1]) :
        isPalindrome = False
        break
if isPalindrome :
    print("Эта строка - палиндром")
else :
    print("Эта строка не палиндром")
print()

# Завдання Python 5_9: Припустимо, є якесь оголошення і кілька різних
# людей, яким потрібно це оголошення відправити. Для цього створюється
# заготовка з вмістом оголошення, всередині якого є ряд змінюються
# параметрів: імена людей і назви подій. Вивести один варіант
# підсумкового оголошення на екран. Для завдання імен та назв
# використовувати форматування за допомогою методу format.
print("Завдання Python 5_9:")
print("===")
Data14 = "Шановний (а), {}!\nЗапрошуємо Вас на {}.\nДата події: {}.\nЗ повагою, {}."
Data15 = [ ['name0', 'event0'], ['name1', 'event1'], ['name2', 'event2'], ['name3', 'event3'], ['name4', 'event4'] ]
Data16 = "13 грудня"
Data17 = "Вазген"
Data18 = Data14.format(Data15[2][0], Data15[2][1], Data16, Data17)
print(Data18)
print("===")
Data19 = "Шановний (а), {toArray[0][0]}!\nЗапрошуємо Вас на {toArray[0][1]}.\nДата події: {eventDate}.\nЗ повагою, {eventFrom}."
Data20 = Data19.format(toArray=Data15, eventDate=Data16, eventFrom=Data17)
print(Data20)
print("===")