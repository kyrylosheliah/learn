using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml.Linq;

namespace rwd_lab1
{
    public partial class lab3 : System.Web.UI.Page
    {
        private string resultBase = "Поле редактирования изменилось: ";

        protected void Page_Load(object sender, EventArgs e)
        {
            if (this.IsPostBack) return; // Только один раз
            Title.Text = "Привет, как Вас зовут?";
            Name.Text = "ФИО";
            Address.Text = "ААА";
        }
        protected void TextBox_TextChanged(object sender, EventArgs e)
        {
            Result.Text = resultBase
                + "<br>Первое поле содержит: " + Name.Text
                + "<br>Второе поле содержит: " + Address.Text;
        }
        protected void Button_Click(object sender, EventArgs e)
        {
            Title.Text = Name.Text + "<br>"
                + "находится по адресу:<br>"
                + Address.Text;
            Result.Text = string.Empty;
        }
    }
}