using Microsoft.Ajax.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_3_Login : System.Web.UI.Page
    {

        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void LoginAction_Click(object sender, EventArgs e)
        {
            this.Validate();// Исполнить валидаторы на сервере
            if (!this.IsValid)// Оценить флаг достоверности
                return;// Отправить назад как есть

            // Извлечь из web.config и сравнить с введенным 
            if (FormsAuthentication.Authenticate(UsernameText.Text, PasswordText.Text))
            {
                // Создать временный cookie-набор (второй параметр false),
                // записать в него  метку аутентификации и перенаправить
                // на исходную запрошенную страницу или MyDefault.aspx
                FormsAuthentication.RedirectFromLoginPage(UsernameText.Text, true);
            }
            else
            {
                HtmlGenericControl message = new HtmlGenericControl();
                AuthResultWrapper.InnerHtml = "<br/><h2 style='color: Red'>Неверное имя или пароль!</h2>";
                //Master.FormWrapper.Controls.Add(message);
            }
        }
    }
}