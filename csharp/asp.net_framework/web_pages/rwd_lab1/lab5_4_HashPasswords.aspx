<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab5_4_HashPasswords.aspx.cs" Inherits="rwd_lab1.lab5_4_HashPasswords" %>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">
    <h1>Административная страница хеширования паролей в Web.config</h1>
    <p><asp:Button ID="btnHashedPwd" runat="server" OnClick="btnHashedPwd_Click" Text="Хешировать" /></p>
    <p><asp:Label ID="lblHashResult" runat="server"></asp:Label></p>
    <p><asp:Label ID="Label1" runat="server">Повторно не выполнять - захешируются уже существующие хеши</asp:Label></p>

    <br />
    <br />
    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab5_3_Login.aspx">Назад</asp:HyperLink></asp:TableCell>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab5_5_SetCookiePersistance.aspx">Вперед</asp:HyperLink></asp:TableCell>
        </asp:TableRow>
    </asp:Table>
</asp:Content>
