using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_9_UserList : System.Web.UI.Page
    {

        // Вынесли поле класса для видимости в обработчиках
        MembershipUserCollection myUsers = new MembershipUserCollection();
        protected void Page_Load(object sender, EventArgs e)
        {
            // Скрываем таблицу деталей
            tableDetails.Visible = false;
            lblUser.Visible = false;
            if (checkUser.Checked)
            {
                // Извлекаем одного пользователя
                if (txtUser.Text.Length == 0)
                {
                    lblUsersList.Text = "Введите имя пользователя";
                    return;
                }
                try // Попытка
                {
                    string user = Server.HtmlEncode(txtUser.Text);
                    myUsers = new MembershipUserCollection();
                    myUsers.Add(Membership.GetUser(user));
                }
                catch // Откат
                {
                    lblUsersList.Text = "Пользователь не найден";
                    return;
                }
            }
            else
            {
                // Извлекаем всех пользователей
                myUsers = Membership.GetAllUsers();
            }
            // Подключаем к сетке извлеченную информации и наполняем элемент
            UsersGridView.DataSource = myUsers;
            UsersGridView.DataBind();
        }
        // Обработчик щелчков на ссылки столбца отображения деталей
        protected void UsersGridView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (UsersGridView.SelectedIndex >= 0)
            {
                // Заполняем интерфейсные элементы отображаемой информацией,
                // адресуясь к конкретному пользователю по ключевому имени,
                // заданному параметром DataKeyNames="UserName" элемента GridView 
                MembershipUser currentUser =
                    myUsers[(string)UsersGridView.SelectedValue];
                lblUserName.Text = currentUser.UserName;
                lblEmail.Text = currentUser.Email;
                lblPasswordQuestion.Text = currentUser.PasswordQuestion;
                lblLastLoginDate.Text = currentUser.LastLoginDate.ToLongDateString();
                txtComment.Text = currentUser.Comment;
                checkIsApproved.Checked = currentUser.IsApproved;
                checkIsLockedOut.Checked = currentUser.IsLockedOut;

                // Включаем видимость таблицы деталей
                tableDetails.Visible = true;
                lblUser.Visible = true;
            }
        }
    }
}