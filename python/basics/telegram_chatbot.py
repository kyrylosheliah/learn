import telebot
from telebot import types
bot = telebot.TeleBot('')
RPS_moves = ["Камінь","Ножиці","Папір"]
RPS_signs = {"Камінь": "✊", "Ножиці": "✂","Папір": " "}
RPS_antimoves = ["Папір","Камінь","Ножиці"]

user_dict = {}

class User:

    def __init__(self):
        self.name = ""
        self.age = 0
        self.RPS_frequencies = [0, 0, 0]
        self.RPS_memory = ""
        self.RPS_stage = False
        self.RPS_bot_won_count = 0
        self.RPS_player_won_count = 0

def get_name_offer(message):
    bot.send_message(message.chat.id, "Як я повинен до тебе звертатися?")

def get_name_acknowledgement(message):
    global user_dict
    user_dict[message.chat.id].name = message.text
    keyboard = types.InlineKeyboardMarkup()
    key_yes = types.InlineKeyboardButton(text='Так', callback_data='get_name_Так')
    keyboard.add(key_yes)
    key_no= types.InlineKeyboardButton(text='Ні', callback_data='get_name_Ні')
    keyboard.add(key_no)
    question = 'Тебе зовуть '+user_dict[message.chat.id].name+'?'
    bot.send_message(message.chat.id, text=question, reply_markup=keyboard)

def get_age_offer(message):
    bot.send_message(message.chat.id, "Введи свій вік")

def get_age_acknowledgement(message):
    global user_dict
    try:
        user_dict[message.chat.id].age = int(message.text)
    except Exception:
        bot.send_message(message.chat.id, 'Введіть число');
    keyboard = types.InlineKeyboardMarkup()
    key_yes = types.InlineKeyboardButton(text='Так', callback_data='get_age_Так')
    keyboard.add(key_yes)
    key_no= types.InlineKeyboardButton(text='Ні', callback_data='get_age_Ні')
    keyboard.add(key_no)
    question = 'Тобі '+str(user_dict[message.chat.id].age)+' років?'
    bot.send_message(message.chat.id, text=question, reply_markup=keyboard)

def rps_acknowledgement(message):
    global user_dict
    if user_dict[message.chat.id].RPS_stage:
        keyboard = types.InlineKeyboardMarkup()
        key_rock = types.InlineKeyboardButton(text='Камінь ✊', callback_data='rps_Камінь')
        keyboard.add(key_rock)
        key_scissors = types.InlineKeyboardButton(text='Ножиці ✂', callback_data='rps_Ножиці')
        keyboard.add(key_scissors)
        key_paper = types.InlineKeyboardButton(text='Папір ', callback_data='rps_Папір')
        keyboard.add(key_paper)
        key_no = types.InlineKeyboardButton(text='Годі ❌', callback_data='rps_Годі')
        keyboard.add(key_no)
        question = user_dict[message.chat.id].name+", "+str(user_dict[message.chat.id].age)+"років, ти обираеш:"
        bot.send_message(message.chat.id, text=question, reply_markup=keyboard)

def rps_offer(message):
    global user_dict
    if user_dict[message.chat.id].RPS_stage:
        if (user_dict[message.chat.id].RPS_memory=="Камінь") or (user_dict[message.chat.id].RPS_memory=="Ножиці") or (user_dict[message.chat.id].RPS_memory=="Папір"):
            user_dict[message.chat.id].RPS_frequencies[RPS_moves.index(user_dict[message.chat.id].RPS_memory)] += 1
            bot_move = RPS_antimoves[user_dict[message.chat.id].RPS_frequencies.index(max(user_dict[message.chat.id].RPS_frequencies))]
            if user_dict[message.chat.id].RPS_memory == RPS_antimoves[RPS_moves.index(bot_move)]:
                user_dict[message.chat.id].RPS_player_won_count += 1
                bot.send_message(message.chat.id, "Ти переміг, "+RPS_signs[user_dict[message.chat.id].RPS_memory]+" б'є "+RPS_signs[bot_move])
            else:
                if bot_move == RPS_antimoves[RPS_moves.index(user_dict[message.chat.id].RPS_memory)]:
                    user_dict[message.chat.id].RPS_bot_won_count += 1
                    bot.send_message(message.chat.id, "Я переміг, "+RPS_signs[bot_move]+" б'є"+RPS_signs[user_dict[message.chat.id].RPS_memory])
                else:
                    bot.send_message(message.chat.id, "Нічия!")
            bot.send_message(message.chat.id, "Перемог ігрока: "+str(user_dict[message.chat.id].RPS_player_won_count)+"\nПеремог Бота: "+str(user_dict[message.chat.id].RPS_bot_won_count))
        else:
            bot.send_message(message.chat.id, "Тисни на кнопку!")
        rps_acknowledgement(message)

# @bot.message_handler(commands=['play', 'help', 'start'])
@bot.message_handler(content_types=['text'])
def get_commands(message):
    global user_dict
    bot.send_message(message.chat.id, "Опції: /help /play /data")
    if message.text.lower() == "/play":
        user_dict[message.chat.id] = User()
        bot.register_next_step_handler(message, get_name_acknowledgement)
        get_name_offer(message)
    elif message.text.lower() == "/help":
        bot.send_message(message.chat.id, "Доступні команди:\n/help - Опис команд\n/play - Зіграй зі мною у камінь-ножиці-папір\n/data - Переглянути, яку інформацію про вас збирає бот")
    elif message.text.lower() == "/data":
        if message.chat.id in user_dict:
            bot.send_message(
                message.chat.id,
                "name: "+user_dict[message.chat.id].name+
                "\nage:"+str(user_dict[message.chat.id].age)+
                "\nfrequencies: "+str(user_dict[message.chat.id].RPS_frequencies)+
                "\nmemory: "+user_dict[message.chat.id].RPS_memory+
                "\nis game stage: "+str(user_dict[message.chat.id].RPS_stage)+
                "\nbot won count: "+str(user_dict[message.chat.id].RPS_bot_won_count)+
                "\nplayer won count: "+str(user_dict[message.chat.id].RPS_player_won_count))
        else:
            bot.send_message(message.chat.id, "Інфомації про вас ще нема, пиши /play")
    else:
        bot.send_message(message.chat.id, "Зіграємо?\nНабирай /play")

@bot.callback_query_handler(func=lambda call: call.data == 'rps_Камінь')
def handle_rps_r(call):
    global user_dict
    bot.register_next_step_handler(call.message, rps_offer)
    user_dict[call.message.chat.id].RPS_memory = "Камінь"
    rps_offer(call.message)

@bot.callback_query_handler(func=lambda call: call.data == 'rps_Ножиці')
def handle_rps_s(call):
    global user_dict
    bot.register_next_step_handler(call.message, rps_offer)
    user_dict[call.message.chat.id].RPS_memory = "Ножиці"
    rps_offer(call.message)

@bot.callback_query_handler(func=lambda call: call.data == 'rps_Папір')
def handle_rps_p(call):
    global user_dict
    bot.register_next_step_handler(call.message, rps_offer)
    user_dict[call.message.chat.id].RPS_memory = "Папір"
    rps_offer(call.message)

@bot.callback_query_handler(func=lambda call: call.data == 'rps_Годі')
def handle_rps_break(call):
    global user_dict
    bot.send_message(call.message.chat.id, "Добре")
    # user_dict[call.message.chat.id].RPS_memory = ""
    user_dict[call.message.chat.id].RPS_stage = False
    bot.register_next_step_handler(call.message, get_commands)

@bot.callback_query_handler(func=lambda call: call.data == 'get_name_Так')
def handle_name_yes(call):
    bot.register_next_step_handler(call.message, get_age_acknowledgement)
    get_age_offer(call.message)

@bot.callback_query_handler(func=lambda call: call.data == 'get_age_Так')
def handle_age_yes(call):
    global user_dict
    bot.register_next_step_handler(call.message, rps_acknowledgement)
    user_dict[call.message.chat.id].RPS_stage = True
    rps_offer(call.message)

@bot.callback_query_handler(func=lambda call: call.data == 'get_name_Ні')
def handle_name_no(call):
    bot.register_next_step_handler(call.message, get_name_acknowledgement)
    get_name_offer(call.message)

@bot.callback_query_handler(func=lambda call: call.data == 'get_age_Ні')
def handle_age_no(call):
    bot.register_next_step_handler(call.message, get_age_acknowledgement)
    get_age_offer(call.message)

bot.enable_save_next_step_handlers(delay=2)
bot.load_next_step_handlers()
bot.polling(none_stop=True)