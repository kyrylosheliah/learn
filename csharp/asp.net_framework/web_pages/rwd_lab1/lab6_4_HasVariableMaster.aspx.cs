using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab6_4_HasVariableMaster : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Page_PreInit(object sender, EventArgs e)
        {
            if (Request.Browser.Cookies)
            {
                if (Request.Cookies["masterpage"] != null)
                { 
                    if (Request.Cookies["masterpage"].Value == "1")
                    {
                        Page.MasterPageFile = "lab6_1_masterpage.master";
                    }
                    else
                    {
                        Page.MasterPageFile = "lab6_4_masterpage2.master";
                    }
                }
            }
        }

        protected void btn_ChangeMasterPage_Click(object sender, EventArgs e)
        {
            if (Request.Browser.Cookies)
            {
                if (Request.Cookies["masterpage"] != null)
                {
                    if (Request.Cookies["masterpage"].Value == "1")
                    {
                        Response.Cookies["masterpage"].Value = "2";
                    }
                    else
                    {
                        Response.Cookies["masterpage"].Value = "1";
                    }
                }
                else
                {
                    HttpCookie mpage = new HttpCookie("masterpage");
                    mpage.Expires = DateTime.Now.AddDays(1);
                    mpage.Value = "2";
                    Response.Cookies.Add(mpage);
                }
            }
            Response.Redirect(Request.RawUrl);
        }

    }
}