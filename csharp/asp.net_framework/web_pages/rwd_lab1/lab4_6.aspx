<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab4_6.aspx.cs" Inherits="rwd_lab1.lab4_6" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableRow>
                <asp:TableCell ColSpan="4" align="center">
                    <asp:ListBox ID="ListBox1" runat="server" AutoPostBack="true"></asp:ListBox>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell Width="200" align="center">
                    <strong>id</strong>
                </asp:TableCell>
                <asp:TableCell Width="200" align="center">
                    <strong>Title</strong>
                </asp:TableCell>
                <asp:TableCell Width="200" align="center">
                    <strong>Teacher</strong>
                </asp:TableCell>
                <asp:TableCell Width="200" align="center">
                    <strong>Type</strong>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center" runat="server">
                    <%= GetTableField("id") %>
                </asp:TableCell>
                <asp:TableCell align="center" runat="server">
                    <%= GetTableField("Title") %>
                </asp:TableCell>
                <asp:TableCell align="center" runat="server">
                    <%= GetTableField("Teacher") %>
                </asp:TableCell>
                <asp:TableCell align="center" runat="server">
                    <%= GetTableField("Type") %>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell ColSpan="2" Width="300" align="center"><asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab4_5.aspx">Назад</asp:HyperLink></asp:TableCell>
                <asp:TableCell ColSpan="2" Width="300" align="center"><asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab4_7.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>
    </div>
</asp:Content>