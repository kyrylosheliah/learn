using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab3_2 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void ActorList_SelectedIndexChanged(object sender, EventArgs e)
        {
            Actor.Text = "___";
            List<string> itemList = new List<string>();
            foreach (var item in CheckBoxList1.Items)
            {
                var checkItem = (ListItem)item;
                if (checkItem.Selected)
                {
                    itemList.Add(checkItem.Text);
                }
            }
            Actor.Text = string.Join(" | ", itemList);
        }

        protected void HeadList_SelectedIndexChanged(object sender, EventArgs e)
        {
            Head.Text = "___";
            foreach (var item in RadioButtonList1.Items)
            {
                var checkItem = (ListItem)item;
                if (checkItem.Selected)
                {
                    Head.Text = checkItem.Text;
                    return;
                }
            }
        }
    }
}