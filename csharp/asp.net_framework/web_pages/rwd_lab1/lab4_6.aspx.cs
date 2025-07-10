using System;
using System.Collections.Generic;
using System.Data.OleDb;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab4_6 : System.Web.UI.Page
    {
        public DataTable savedTable;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (IsPostBack) return;

            TableContext();

            foreach (DataRow row in savedTable.Rows)
            {
                string id = row["id"].ToString();
                string Title = row["Title"].ToString();
                ListBox1.Items.Add(new ListItem(id + ": " + Title, id));
            }
            //ListBox1.DataSource = myDS.Tables["lesson"].DefaultView;
            //ListBox1.DataBind();
        }

        protected void TableContext()
        {
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
            DataView dataView = myDS.Tables["lesson"].DefaultView;
            savedTable = dataView.Table;
            cn.Close();
        }

        protected void TableRow(string id)
        {
            OleDbConnection cn = new OleDbConnection();
            cn.ConnectionString = "Provider=Microsoft.ACE.OLEDB.16.0;"
                + "Data Source=" + HttpRuntime.AppDomainAppPath + "\\db_access\\task4.mdb";
            cn.Open();
            // Формируется строка SQL запроса данных из источника 
            string str = "SELECT * from lesson where id="+id;
            // Происходит соединение с базой данных 
            // с помощью управляемого провайдера OLE DB 
            OleDbDataAdapter dAdapt = new OleDbDataAdapter(str, cn);
            // Получение данных из источника 
            DataSet myDS = new DataSet("lessons");
            dAdapt.Fill(myDS, "lesson");
            // Заполнение таблицы данными 
            DataView dataView = myDS.Tables["lesson"].DefaultView;
            savedTable = dataView.Table;
            cn.Close();
        }

        protected string GetTableField(string field)
        {
            if (ListBox1.SelectedItem == null)
            {
                return "___";
            }
            TableRow(ListBox1.SelectedItem.Value);
            return savedTable.Rows[0][field].ToString();
        }
    }
}