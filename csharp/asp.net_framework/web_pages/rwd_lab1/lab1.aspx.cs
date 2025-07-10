using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            Debug.AutoFlush = true;
        }
        private static bool clickFlag = true;
        private static string[] texts = {
            "Текст 1, перший клік",
            "Інший текст другого кліку"
        };
        protected void ReplaceButton_Click(object sender, EventArgs e)
        {
            clickFlag = !clickFlag;
            MessageLabel.Text = texts[clickFlag ? 1 : 0];
            // Debug.WriteLine(clickFlag ? 1 : 0);
        }
    }
}