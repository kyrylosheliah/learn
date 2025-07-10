using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab7_5_RegisterMultiview : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                DropDownList1.DataSource = User_Registration.Views;
                DropDownList1.DataTextField = "ID";
                DropDownList1.DataBind();
                User_Registration.ActiveViewIndex = 0;
            }
        }

        protected void User_Registration_Prev(object sender, EventArgs e)
        {
            if (User_Registration.ActiveViewIndex != 0)
            {
                --User_Registration.ActiveViewIndex;
            }
        }

        protected void User_Registration_Next(object sender, EventArgs e)
        {
            if (User_Registration.ActiveViewIndex != (User_Registration.Views.Count - 1))
            {
                ++User_Registration.ActiveViewIndex;
            }
        }

        protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
        {
            User_Registration.ActiveViewIndex = DropDownList1.SelectedIndex;
        }

        protected void User_Registration_ActiveViewChanged(object sender, EventArgs e)
        {
            DropDownList1.SelectedIndex = User_Registration.ActiveViewIndex;
        }
    }
}