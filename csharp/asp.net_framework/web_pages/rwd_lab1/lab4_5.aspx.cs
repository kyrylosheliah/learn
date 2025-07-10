﻿using System;
using System.Collections.Generic;
using System.Data.OleDb;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab4_5 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (IsPostBack) return;
            
            // Подключение к источнику данных
            OleDbConnection cn = new OleDbConnection();
            cn.ConnectionString = "Provider=Microsoft.ACE.OLEDB.16.0;"
                + "Data Source=" + HttpRuntime.AppDomainAppPath + "\\db_access\\task4.mdb";
            cn.Open();
            // Формируется строка SQL запроса данных из источника 
            string str = "SELECT * from lesson";
            // Происходит соединение с базой данных 
            // с помощью управляемого провайдера OLE DB 
            OleDbDataAdapter dAdapt = new OleDbDataAdapter(str, cn);
            // Получение данных из источника 
            DataSet myDS = new DataSet("lessons");
            dAdapt.Fill(myDS, "lesson");
            // Заполнение таблицы данными 
            DataList2.DataSource = myDS.Tables["lesson"].DefaultView;
            DataList2.DataBind();
            cn.Close();
        }
    }
}