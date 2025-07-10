using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab4_2 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (this.IsPostBack) return;// Только для инициализации
            ArrayList Cities = new ArrayList(); // Создать промежуточный источник
            Cities.Add("Киев");           // Добавить...
            Cities.Add("Днепр");
            Cities.Add("Запорожье");
            Cities.Add("Мариуполь");
            Cities.Add("Винница");
            Cities.Add("Одесса");
            Cities.Add("Житомир");
            Cities.Add("Львов");
            Cities.Add("Ужгород");
            ListBox1.DataSource = Cities;// Связать
            ListBox1.DataBind(); // Загрузить
            ListBox1.Rows = ListBox2.Rows = 6; // Высота списков в строках
        }
        protected void Button1_Click(object sender, EventArgs e)
        {
            // Создаем коллекцию для временного хранения строк списка
            ListItemCollection tmp = new ListItemCollection();
            // Перебираем левый список и ищем выделенное
            foreach (ListItem s in ListBox1.Items)
            {
                if (s.Selected)
                    tmp.Add(s);
            }
            // Слева уничтожаем, справа добавляем то, что нашли выделенное
            foreach (ListItem s in tmp)
            {
                ListBox1.Items.Remove(s);
                ListBox2.Items.Add(s);
            }
        }
        protected void Button2_Click(object sender, EventArgs e)
        {
            // Создаем коллекцию для временного хранения строк списка
            ListItemCollection tmp = new ListItemCollection();
            // Перебираем правый список и ищем выделенное
            foreach (ListItem s in ListBox2.Items)
            {
                if (s.Selected)
                    tmp.Add(s);
            }
            // Справа уничтожаем, слева добавляем то, что нашли выделенное
            foreach (ListItem s in tmp)
            {
                ListBox2.Items.Remove(s);
                ListBox1.Items.Add(s);
            }
        }

    }
}