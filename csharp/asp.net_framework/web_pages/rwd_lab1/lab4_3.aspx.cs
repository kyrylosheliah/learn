using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab4_3 : System.Web.UI.Page
    {
        // Объявляем ссылку на поставщика данных
        protected System.Data.SqlClient.SqlDataAdapter DSAdapter;

        // Объявляем ссылку на набор данных 
        protected System.Data.DataSet ProductsData;

        // Создаем SQL-команду для выборки данных поставщиком
        protected System.String cmd = "SELECT ProductID, ProductName FROM Products";

        protected void Page_Load(object sender, EventArgs e)
        {
            if (this.IsPostBack) return;// Только для инициализации

            // Создали поставщик данных с нужными настройками
            DSAdapter = new System.Data.SqlClient.SqlDataAdapter(
                cmd, "server=(localdb)\\rwdan_lab4; uid=; pwd=; database=northwind");

            // Создали набор данных
            ProductsData = new DataSet();

            // Заполнили набор данными из поставщика
            DSAdapter.Fill(ProductsData, "Products");

            // Подсоединяем список к набору данных как источнику данных
            ProductsList.DataSource = ProductsData.Tables["Products"].DefaultView;

            // Указываем, из какой колонки брать видимые тексты элементов списка
            ProductsList.DataTextField = "ProductName";

            // Указываем, из какой колонки брать невидимые значения элементов списка
            ProductsList.DataValueField = "ProductID";

            // Заполняем список из присоединенного источника данных ProductsData
            ProductsList.DataBind();

            // Выводим в текстовую метку выделенное значение
            ProductSelection.Text = ProductsList.SelectedItem.Value;

            FillPage(this, new EventArgs());
        }

        protected void FillPage(object sender, EventArgs e)
        {
            foreach (ListItem item in ProductsList.Items)
            {
                TableRow toRow = new TableRow();
                TableCell toCell_ProductName = new TableCell();
                TableCell toCell_ProductQuantity = new TableCell();
                //toCell_ProductName.Attributes["ColSpan"] = "2";
                toCell_ProductName.Text = item.Text;
                toCell_ProductQuantity.Text = item.Value;
                toRow.Cells.Add(toCell_ProductName);
                toRow.Cells.Add(toCell_ProductQuantity);
                Table2.Rows.Add(toRow);
            }
        }

        protected void ProductsList_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Выводим в текстовую метку выделенное значение
            ProductSelection.Text = ProductsList.SelectedItem.Value;

            FillPage(this, new EventArgs());
        }

    }
}