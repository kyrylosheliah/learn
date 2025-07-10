using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Configuration;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_4_HashPasswords : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnHashedPwd_Click(object sender, EventArgs e)
        {
            // Загрузить содержимое корневого Web.config
            Configuration myConfig = WebConfigurationManager.OpenWebConfiguration("~/");
            // Найти содержимое секции system.web
            ConfigurationSectionGroup systemWeb = myConfig.SectionGroups["system.web"];
            // Найти содержимое секции authentication 
            AuthenticationSection authSec = (AuthenticationSection)systemWeb
                .Sections["authentication"];
            // Установить параметр passwordFormat, сообщающий, что было хеширование по MD5
            authSec.Forms.Credentials.PasswordFormat = FormsAuthPasswordFormat.MD5;
            // Извлекаем из коллекции Users старые имена и пароли 
            int count = authSec.Forms.Credentials.Users.Count;
            string[] name = new string[count];
            string[] clearTextPwd = new string[count];
            int i = 0;
            foreach (FormsAuthenticationUser user in authSec.Forms.Credentials.Users)
            {
                name[i] = user.Name;
                clearTextPwd[i] = user.Password;
                i++;
            }
            // Очищаем коллекцию Users 
            authSec.Forms.Credentials.Users.Clear();
            // Добавляем старые имена и новые хешированные пароли
            for (i = 0; i < count; i++)
            {
                // Хешируем исходный пароль
                string hashedPwd = FormsAuthentication
                    .HashPasswordForStoringInConfigFile(clearTextPwd[i], "MD5");
                // Добавляем в коллекцию Users
                authSec.Forms.Credentials.Users
                    .Add(new FormsAuthenticationUser(name[i], hashedPwd));
            }
            // Обновляем файл Web.config 
            myConfig.Save();
            // Отсылаем сообщение 
            lblHashResult.Text = "Хеширование завершено.<br />";
        }
    }
}