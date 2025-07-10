using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_6_Login : System.Web.UI.Page
    {
        protected bool isLogin = true;

        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void LoginAction_Click(object sender, EventArgs e)
        {
            this.Validate();// Исполнить валидаторы на сервере
            if (!this.IsValid)// Оценить флаг достоверности
                return;// Отправить назад как есть

            // Извлечь из базы данных и сравнить с введенным 
            if (Membership.ValidateUser(Login_Username.Text, Login_Password.Text))
            {
                // Создать временный cookie-набор (второй параметр false),
                // записать в него  метку аутентификации и перенаправить
                // на исходную запрошенную страницу или defaultUrl="MyDefault.aspx"
                // с созданием coockie-набора только на период сеанса
                FormsAuthentication.RedirectFromLoginPage(Login_Username.Text, false);
            }
            else
            {
                AuthResultWrapper.InnerHtml = "<h2 style='color: Red'>Неверное имя или пароль!</h2>";
            }
        }


    }
}