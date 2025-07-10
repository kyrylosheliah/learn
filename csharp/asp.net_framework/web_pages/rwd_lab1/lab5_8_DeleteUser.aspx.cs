using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_8_DeleteUser : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void DeleteUser_Click(object sender, EventArgs e)
        {
            if (Membership.DeleteUser(username.Text))
            {
                lblResult.Text = "Пользователь " + username.Text
                    + " успешно удален";
                username.Text = "";
            }
            else
            {
                lblResult.Text = "Пользователь не удален";
                lblResult.ForeColor = System.Drawing.Color.Red;
            }
        }
    }
}