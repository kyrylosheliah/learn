using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab2_5 : System.Web.UI.Page
    {

        protected void Page_Load(object sender, EventArgs e)
        {

            PrevLink.HRef = "lab2_4";
            NextLink.HRef = "lab2";
        }
    }
}