using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace rwd_lab1
{
    /// <summary>
    /// Summary description for lab8_2_WebServiceControl
    /// </summary>
    [WebService(Namespace = "http://microsoft.com/webservices/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class lab8_2_WebServiceControl : System.Web.Services.WebService
    {

        [WebMethod]
        public string CurrentDayOfWeek()
        {
            return DateTime.Now.DayOfWeek.ToString();
        }


        [WebMethod]
        public string CurrentDayOfMonth()
        {
            return DateTime.Now.Day.ToString();
        }


        [WebMethod]
        public string CurrentDayOfYear()
        {
            return DateTime.Now.DayOfYear.ToString();
        }
    }
}
