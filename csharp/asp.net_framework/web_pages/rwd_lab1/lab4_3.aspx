<%@ Page Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab4_3.aspx.cs" Inherits="rwd_lab1.lab4_3" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableHeaderRow>
                <asp:TableHeaderCell ColSpan="3" align="center"><h1 style="text-align:center">Соединение раскрывающегося списка с базой данных Northwind</h1></asp:TableHeaderCell>
            </asp:TableHeaderRow>
            <asp:TableRow>
                <asp:TableCell ColSpan="3" align="center">Выделите элемент в списке и получите дополнительные сведения</asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center" Width="300">
                    <asp:DropDownList OnSelectedIndexChanged="ProductsList_SelectedIndexChanged" ID="ProductsList" runat="server" AutoPostBack="True" Width="100%"></asp:DropDownList>
                </asp:TableCell>
                <asp:TableCell align="center" Width="300">
                    Запасы выделенного товара:
                </asp:TableCell>
                <asp:TableCell align="center" Width="300">
                    <asp:Label ID="ProductSelection" runat="server" Font-Bold="True">_</asp:Label>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center"><asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab4_2.aspx">Назад</asp:HyperLink></asp:TableCell>
                <asp:TableCell align="center">&nbsp;</asp:TableCell>
                <asp:TableCell align="center"><asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab4_4.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>
        <br />
        <hr />
        <br />
        <asp:Table border="1" style="width:100%;" ID="Table2" runat="server">
            <asp:TableHeaderRow>
                <asp:TableHeaderCell Width="300"><strong>Product</strong></asp:TableHeaderCell>
                <asp:TableHeaderCell Width="300"><strong>Quantity</strong></asp:TableHeaderCell>
            </asp:TableHeaderRow>
        </asp:Table>
    </div>
</asp:Content>