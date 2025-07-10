<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab5_1_addusers.aspx.cs" Inherits="rwd_lab1.lab5_1_addusers" %>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">
    <h1>Административная страница добавления учетных записей в Web.config</h1>
    <p>
        <asp:Button ID="btnAddUsers" runat="server" Text="Добавить" OnClick="btnAddUsers_Click" />
    </p>
    <p>
        <asp:Label ID="lblUsersResult" runat="server"></asp:Label>
    </p>

    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab5_2_Default.aspx">Вперед</asp:HyperLink></asp:TableCell>
        </asp:TableRow>
    </asp:Table>
</asp:Content>
