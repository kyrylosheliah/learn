using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_2_Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void SignOutAction_Click(object sender, EventArgs e)
        {
            // Уничтожить cookie-набор 
            FormsAuthentication.SignOut();
            // Направить на страницу регистрации
            FormsAuthentication.RedirectToLoginPage();
        }
    }
}