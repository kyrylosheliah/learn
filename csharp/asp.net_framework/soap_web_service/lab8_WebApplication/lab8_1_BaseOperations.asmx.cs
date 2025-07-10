using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace lab8_WebApplication
{
    /// <summary>
    /// Summary description for lab8_1_BaseOperations
    /// </summary>
    [WebService(Namespace = "http://microsoft.com/webservices/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class lab8_1_BaseOperations : System.Web.Services.WebService
    {
        [WebMethod]
        public string Binary(int x)
        {
            return Convert.ToString(x, 2);
        }

        [WebMethod]
        public string Octal(int x)
        {
            return Convert.ToString(x, 8);
        }
        [WebMethod]
        public string Hexadecimal(int x)
        {
            return Convert.ToString(x, 16);
        }
    }
}
