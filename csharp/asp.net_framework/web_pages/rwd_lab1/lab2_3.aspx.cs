using Microsoft.Ajax.Utilities;
using System;
using System.Collections.Generic;
using System.EnterpriseServices;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab2_3 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            NextLink.HRef = "~/lab2_4";
            PrevLink.HRef = "~/lab2_2";
        }
        static private bool textFlag = false;
        protected void ColorButton_ServerClick(object sender, EventArgs e)
        {
            //HtmlGenericControl body = Master.FindControl("BodyID") as HtmlGenericControl;
            ContentWrapper.Attributes["class"] = PageColor.Value;
        }
        protected void SizeButton_ServerClick(object sender, EventArgs e)
        {
            FontID.Attributes["size"] = FontSize.Value;
        }
        protected void AddButton_ServerClick(object sender, EventArgs e)
        {
            if (!textFlag)
            {
                Text0.InnerHtml = "Нажмите на кнопку и сервер уберет две новых строки";
                Text1.InnerHtml = "<h1><font color='red'>Разработка Веб-приложений ASP.NET</font></h1>";
                Text2.InnerHtml = "<h1><font color='blue'>У Вас все получается!!!</font></h1>";
                AddButton.Value = "Убрать строки";
                textFlag = true;
            }
            else
            {
                Text0.InnerHtml = "Нажмите на кнопку и сервер добавит две новых строки";
                Text1.InnerHtml = "";
                Text2.InnerHtml = "";
                AddButton.Value = "Добавить строки";
                textFlag = false;
            }
        }

    }
}