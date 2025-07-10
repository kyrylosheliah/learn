# Завдання Python 3.0: Створити процедуру, яка обчислює різницю двох
# чисел, які вводить користувач. Виконати завдання двома способами: 1)
# процедура без параметрів: числа - глобальні змінні, визначені в основній
# програмі; 2) процедура з параметрами: числа - параметри процедури.
def substract_local(from_number, a_number):
    print("Operation with function params:", from_number, "-", a_number, "=", from_number - a_number)

global_from_todiff = float(0)
global_a_todiff = float(0)

def substract_global() :
    global global_from_todiff
    global global_a_todiff
    print("Operation with global params:", global_from_todiff, "-", global_a_todiff, "=", global_from_todiff - global_a_todiff)

# Завдання Python 3.1: Напишіть процедуру, яка виводить на екран в
# стовпчик всі цифри переданого їй числа, починаючи з останньої:
# число: 4673
# результат:
# 3
# 7
# 6
# 4
def unstack_list_print(unlist) :
    while unlist :
        print(unlist.pop())

# Завдання Python 3.2: Напишіть процедуру, яка виводить на екран всі
# подільники переданого їй числа (в один рядок).
def divider_print(number) :
    result_dividers = "Dividers for " + str(number) + " are: "
    for i in range(number, 1, -1) :
        if not(number % i) :
            result_dividers += " " + str(i)
    print(result_dividers)

# Завдання Python 3.3: Скласти програму з процедурою для обчислення
# ступеня числа (вхідні параметри: число і ступінь).
def power(a_number, to_number) :
    print(a_number,"**",to_number,"=",a_number**to_number)

# Завдання Python 3.4: Напишіть процедуру, яка приймає параметр -
# натуральне число N - і виводить перші N чисел Фібоначчі.
def fibonacci_print(count) :
    fib1 = 1
    fib2 = 1
    print("Fibonacci sequence lenght is", count)
    i = 2
    print("The 1 element is", fib1)
    print("The 2 element is", fib2)
    while i < count :
        i += 1
        fib_sum = fib1 + fib2
        fib1 = fib2
        fib2 = fib_sum
        print("The", i + 1,"element is", fib2)

# Завдання Python 3.5: Напишіть функцію, яка обчислює факторіал
# натурального числа N.
def factorial_print(base):
    result = int(1)
    i = int(base);
    while i >= 2 :
        result *= i
        i -= 1
    print(base,"! = ", result, sep="")

def main() :
    print("===3.0 substract")
    answer1 = float(input("Substract {from} number: "))
    answer2 = float(input("Substract {a} number: "))
    global global_from_todiff
    global_from_todiff = answer1
    global global_a_todiff
    global_a_todiff = answer2
    substract_local(answer1, answer2)
    substract_global()
    print("\n===3.1 unstack")
    answer1 = list(input("Input a number: "))
    unstack_list_print(answer1)
    print("\n===3.2 dividers")
    answer1 = int(input("Input a number: "))
    divider_print(answer1)
    print("\n===3.3 power")
    answer1 = float(input("Power {a} number: "))
    answer2 = float(input("Power {to} number: "))
    power(answer1, answer2)
    print("\n===3.4 fibonacci")
    answer1 = int(input("Pick Fibonacci sequence lenght: "))
    fibonacci_print(answer1)
    print("\n===3.5 factorial")
    answer1 = int(input("Factorial number: "))
    factorial_print(answer1)

main()