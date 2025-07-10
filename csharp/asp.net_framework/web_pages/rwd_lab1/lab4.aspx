<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab4.aspx.cs" Inherits="rwd_lab1.lab4" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableHeaderRow>
                <asp:TableHeaderCell ColSpan="2" align="center"><h1 style="text-align:center">Привязка данных к Веб-элементам управления через промежуточный источник данных</h1></asp:TableHeaderCell>
            </asp:TableHeaderRow>
            <asp:TableRow>
                <asp:TableCell ColSpan="2" align="center">Выберите любой элемент</asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center" Width="300">
                    <asp:RadioButtonList ID="RadioButtonList1" runat="server" AutoPostBack="True">
                        </asp:RadioButtonList>
                </asp:TableCell>
                <asp:TableCell align="center" Width="300">
                    <asp:DropDownList ID="DropDownList1" runat="server" AutoPostBack="True">
                        </asp:DropDownList>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell colspan="2" align="center"><asp:HyperLink ID="HyperLink2" runat="server" NavigateUrl="~/lab4_2.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>
    </div>
</asp:Content>