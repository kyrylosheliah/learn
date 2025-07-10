using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab4 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (this.IsPostBack) return;//Инициализация только раз
            ArrayList Cities = new ArrayList(); //Создать промежуточный источник
            Cities.Add("Киев");         // Добавить...
            Cities.Add("Днепр");
            Cities.Add("Запорожье");
            Cities.Add("Мариуполь");
            Cities.Add("Винница");
            Cities.Add("Одесса");
            Cities.Add("Житомир");
            Cities.Add("Львов");
            Cities.Add("Ужгород");
            DropDownList1.DataSource = Cities;// Связать список с источником
            DropDownList1.DataBind();        // Загрузить список

            RadioButtonList1.DataSource = Cities;// Связать список с источником

            RadioButtonList1.DataBind();      // Загрузить список
                                              // Установить начальные позиции списков
            DropDownList1.SelectedIndex = 0;
            RadioButtonList1.SelectedIndex = DropDownList1.SelectedIndex;
        }
        protected void RadioButtonList1_SelectedIndexChanged(object sender, EventArgs e)
        {
            DropDownList1.SelectedIndex = RadioButtonList1.SelectedIndex;
        }
        protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
        {
            RadioButtonList1.SelectedIndex = DropDownList1.SelectedIndex;
        }

    }
}