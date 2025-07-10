using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab2_4 : System.Web.UI.Page
    {
        const int WIDTH = 400, HEIGHT = 275;
        string[] messages = {
            "<h2>Первый рисунок</h2>",
            "<h2>Второй рисунок</h2>",
            "<h2>Третий рисунок</h2>"};

        protected void Page_Load(object sender, EventArgs e)
        {
            PictureTitle.InnerHtml = messages[0];
            Image.Width = WIDTH;
            Image.Height = HEIGHT;
            Image.Border = 1;
            Image.Src = "/Images/image1.png";
            PrevLink.HRef = "lab2_3";
            NextLink.HRef = "lab2";
        }
        
        protected void PictureButton_ServerClick(object sender, EventArgs e)
        {
            string pictureChoice = SelectPicture.Value;

            switch (pictureChoice)
            {
                case "1":
                    PictureTitle.InnerHtml = messages[0];
                    Image.Src = "/Images/image1.png";
                    break;
                case "2":
                    PictureTitle.InnerHtml = messages[1];
                    Image.Src = "/Images/image2.png";
                    break;
                default:
                    PictureTitle.InnerHtml = messages[2];
                    Image.Src = "/Images/image3.png";
                    break;
            }
        }
    }
}