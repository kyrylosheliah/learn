from datetime import datetime
from StreeterPhelpsModel import Model

river_name = "moschchunka" # назва файлу *river_name*.xls[x]
data_date_format = "%Y" # шаблон форми запису дати в першому стовпці вибірки
model_start_date = datetime(year=2021, month=1, day=1) # дата початку регресії для обчислення kd
model_end_date = datetime(year=2023, month=1, day=1) # 12 31 # дата кінця регресії для обчислення kd
DO_sat = 11.27 # рівень насичення киснем За Хільчевський В.К., характеристика річок басейну Дніпра
dt = 1 # крок часу моделі у днях
T = 20 * 365 # тривалість моделювання у днях
dpi = 94 # щільність пікселів екрану для величини графіків, точок на дюйм

model = Model(river_name, T, dt, data_date_format, dpi)
model.fit(model_start_date, model_end_date, DO_sat)
