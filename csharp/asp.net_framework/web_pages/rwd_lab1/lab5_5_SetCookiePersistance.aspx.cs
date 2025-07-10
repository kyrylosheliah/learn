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
    public partial class lab5_5_SetCookiePersistance : System.Web.UI.Page
    {
        Label message;
        protected void Page_Load(object sender, EventArgs e)
        {
            // Дескриптор центрирования
            HtmlGenericControl center = new HtmlGenericControl("center");
            ContentWrapper.Controls.Add(center);

            // Текстовая метка с заголовком 
            Label label = new Label();
            center.Controls.Add(label);
            label.Text = "<h2>Закрепить аутентификацию за броузером</h2>";
            // Кнопки
            Button createPersistentCookie = new Button();
            center.Controls.Add(createPersistentCookie);
            createPersistentCookie.Text = "Создать бессрочный AuthCookie";
            createPersistentCookie.Click += new EventHandler(createPersistentCookie_Click);
            center.Controls.Add(new HtmlGenericControl("br"));

            Button createTemporaryCookie = new Button();
            center.Controls.Add(createTemporaryCookie);
            createTemporaryCookie.Text = "Создать срочный AuthCookie";
            createTemporaryCookie.Click += new EventHandler(createTemporaryCookie_Click);
            center.Controls.Add(new HtmlGenericControl("br"));

            Button deleteCookie = new Button();
            center.Controls.Add(deleteCookie);
            deleteCookie.Text = "Удалить AuthCookie";
            deleteCookie.Click += new EventHandler(deleteCookie_Click);
            center.Controls.Add(new HtmlGenericControl("br"));

            // Текстовая метка с сообщением
            message = new Label();
            center.Controls.Add(message);
            message.Text = String.Empty;
        }
        void createPersistentCookie_Click(object sender, EventArgs e)
        {
            // Создать бессрочный cookie
            HttpCookie authCookie = FormsAuthentication.GetAuthCookie("xx", true);
            // Отослать на броузер
            this.Response.Cookies.Add(authCookie);
            // Сообщить пользователю
            message.Text = "Бессрочный AuthCookie создан!";
        }
        void createTemporaryCookie_Click(object sender, EventArgs e)
        {
            // Создать вначале бессрочный cookie
            HttpCookie authCookie = FormsAuthentication.GetAuthCookie("xx", true);
            // Настроить его как временный сроком на 10 дней
            authCookie.Expires = DateTime.Now.AddDays(10);
            // Отослать на броузер
            this.Response.Cookies.Add(authCookie);
            // Сообщить пользователю
            message.Text = "Срочный AuthCookie создан!";
        }
        void deleteCookie_Click(object sender, EventArgs e)
        {
            // Удалить cookie-набор регистрации
            FormsAuthentication.SignOut();
            // Сообщить пользователю
            message.Text = "AuthCookie удален!";
        }
    }
}