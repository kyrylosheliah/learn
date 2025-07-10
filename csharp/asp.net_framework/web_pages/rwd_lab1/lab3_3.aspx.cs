using Antlr.Runtime.Misc;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab3_3 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void DropDownList_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (var item in DropDownList1.Items)
            {
                var checkItem = (ListItem)item;
                if (checkItem.Selected)
                {
                    DropDownList_Managable.InnerHtml += " | " + checkItem.Value;
                    return;
                }
            }
        }
        protected void ListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            List<string> itemList = new List<string>();
            foreach (var item in ListBox1.Items)
            {
                var checkItem = (ListItem)item;
                if (checkItem.Selected)
                {
                    itemList.Add(checkItem.Value);
                }
            }
            ListBox_Managable.InnerHtml += "<br>" + string.Join(", ", itemList);
        }
        protected void AdRotator_Managable(object sender, EventArgs e)
        {
            AdRotator1.AdvertisementFile = @"./Ads/Ads1.xml";
        }
        protected void Calendar_SelectionChanged(object sender, EventArgs e)
        {
            Calendar_Managable.InnerHtml += "<br>" + Calendar1.SelectedDate.ToString();
        }
    }
}