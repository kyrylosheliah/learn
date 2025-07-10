using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab6_1_masterpage : System.Web.UI.MasterPage
    {
        public string BannerText
        {
            get { return MasterLabel.Text; }
            set { MasterLabel.Text = value; }
        }

        protected void Page_Load(object sender, EventArgs e)
        {

        }
    }
}