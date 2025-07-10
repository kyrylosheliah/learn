using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_1_addusers : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void btnAddUsers_Click(object sender, EventArgs e)
        {
            // Учетные записи для новых аутентифицированных пользователей
            string[,] authUsers = {
                {"user1", "password1"},
                {"user2", "password2"},
                {"user3", "password3"}
            };
            // Загрузить содержимое корневого Web.config
            Configuration myConfig = System.Web.Configuration
                .WebConfigurationManager.OpenWebConfiguration("~/");
            // Найти содержимое секции system.web
            ConfigurationSectionGroup systemWeb = myConfig.SectionGroups["system.web"];
            // Найти содержимое секции authentication 
            System.Web.Configuration.AuthenticationSection authSec
                = (System.Web.Configuration.AuthenticationSection)systemWeb
                .Sections["authentication"];
            // Установить параметр passwordFormat (Clear, MD5, SHA1) 
            authSec.Forms.Credentials.PasswordFormat
                = System.Web.Configuration.FormsAuthPasswordFormat.Clear;

            // Добавить новых пользователей
            for (int i = 0; i < authUsers.Length / 2; i++)
            {
                authSec.Forms.Credentials.Users
                    .Add(new System.Web.Configuration.FormsAuthenticationUser
                    (authUsers[i, 0], authUsers[i, 1]));
            }
            // Обновить файл Web.config 
            myConfig.Save();
            // Отсылаем сообщение 
            lblUsersResult.Text = "Новые пользователи добавлены!!!";
        }
    }
}