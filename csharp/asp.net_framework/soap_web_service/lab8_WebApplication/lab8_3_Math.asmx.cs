using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace lab8_WebApplication
{
    /// <summary>
    /// Summary description for lab8_3_Math
    /// </summary>
    [WebService(Namespace = "http://microsoft.com/webservices/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class lab8_3_Math : System.Web.Services.WebService
    {
        [WebMethod]
        public double Sum(double a, double b)
        {
            return a + b;
        }

        [WebMethod]
        public double Sub(double a, double b)
        {
            return a - b;
        }

        [WebMethod]
        public double Mul(double a, double b)
        {
            return a * b;
        }

        [WebMethod]
        public double Div(double a, double b)
        {
            return a / b;
        }


        [WebMethod]
        public double Pow(double a, double b)
        {
            return Math.Pow(a, b);
        }
    }
}
