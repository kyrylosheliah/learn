using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace rwd_lab1
{
    /// <summary>
    /// Summary description for Service1
    /// </summary>
    [WebService(Namespace = "http://microsoft.com/webservices/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [ToolboxItem(false)]
    public class lab8_1_WebService : System.Web.Services.WebService
    {
        //InitializeComponent(); 

        [WebMethod]
        public string Binary(int x)
        {
            return Convert.ToString(x, 2);
        }

        // Преобразование в восьмеричную систему счисления

        [WebMethod]
        public string Octal(int x)
        {
            return Convert.ToString(x, 8);
        }

        // Преобразование в шестнадцатиричную систему счисления

        [WebMethod]
        public string Hexadecimal(int x)
        {
            return Convert.ToString(x, 16);
        }
    }
}