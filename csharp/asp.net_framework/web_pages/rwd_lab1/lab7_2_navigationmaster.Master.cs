﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab7_2_navigationmaster : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (SiteMap.CurrentNode.PreviousSibling != null)
            {
                hl_Previous.NavigateUrl = SiteMap.CurrentNode.PreviousSibling.Url;
                hl_Previous.Text = "prev:" + SiteMap.CurrentNode.PreviousSibling.Url;
                hl_Previous.Visible = true;
            }
            else
            {
                hl_Previous.Visible = false;
            }

            if (SiteMap.CurrentNode.NextSibling != null)
            {
                hl_Next.NavigateUrl = SiteMap.CurrentNode.NextSibling.Url;
                hl_Next.Text = "next:" + SiteMap.CurrentNode.NextSibling.Url;
                hl_Next.Visible = true;
            }
            else
            {
                hl_Next.Visible = false;
            }
        }
    }
}