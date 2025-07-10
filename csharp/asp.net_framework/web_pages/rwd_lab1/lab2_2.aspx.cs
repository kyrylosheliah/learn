using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab2_2 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            NextLink.HRef = "~/lab2_3";
            PrevLink.HRef = "~/lab2";
        }

        protected void Message1_ServerClick(object sender, EventArgs e)
        {
            sampID.InnerHtml = "Message1_ServerClick";
        }
        protected void Message2_ServerClick(object sender, EventArgs e)
        {
            sampID.InnerHtml = "Message2_ServerClick";
        }
    }
}