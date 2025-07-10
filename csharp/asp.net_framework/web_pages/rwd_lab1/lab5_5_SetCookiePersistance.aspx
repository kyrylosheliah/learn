<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab5_5_SetCookiePersistance.aspx.cs" Inherits="rwd_lab1.lab5_5_SetCookiePersistance" %>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">
    <div id="ContentWrapper" runat="server">
    
    </div>
    
    <br />
    <br />
    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab5_4_HashPasswords.aspx">Назад</asp:HyperLink></asp:TableCell>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab5_6_Login.aspx">Вперед</asp:HyperLink></asp:TableCell>
        </asp:TableRow>
    </asp:Table>
</asp:Content>
