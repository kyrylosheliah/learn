using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_10_UpdateUser : System.Web.UI.Page
    {

        // Вынесли поле для видимости в обработчиках
        MembershipUserCollection myUsers = new MembershipUserCollection();
        protected void Page_Load(object sender, EventArgs e)
        {
            // Скрываем таблицу деталей
            tableDetails.Visible = false;
            lblUser.Visible = false;

            // Извлекаем всех пользователей
            myUsers = Membership.GetAllUsers();

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
                txtEmail.Text = currentUser.Email;
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
        protected void btnUpdate_Click(object sender, EventArgs e)
        {
            if (UsersGridView.SelectedIndex >= 0)
            {
                // Адресуемся к выделенному пользователю
                MembershipUser currentUser =
                    myUsers[(string)UsersGridView.SelectedValue];
                // Избавляемся от возможных управляющих символов
                // в пользовательском вводе 
                currentUser.Email = Server.HtmlEncode(txtEmail.Text);
                currentUser.Comment = Server.HtmlEncode(txtComment.Text);

                currentUser.IsApproved = checkIsApproved.Checked;
                // Сбрасываем в базу данных 
                Membership.UpdateUser(currentUser);
                // Обновить содержимое GridView из БД, поскольку
                // этот обработчик выполнится после Page_Load
                myUsers = Membership.GetAllUsers();// Извлекаем пользователей
                UsersGridView.DataBind();
            }
        }
    }
}