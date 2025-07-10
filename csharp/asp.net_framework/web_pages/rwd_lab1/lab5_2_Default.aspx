<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab5_2_Default.aspx.cs" Inherits="rwd_lab1.lab5_2_Default" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <h1>Страница с ограниченным доступом Default.aspx</h1>
        <p>
            <asp:Button ID="SignOutAction" runat="server" Text="Отменить регистрацию" OnClick="SignOutAction_Click" />
        </p>

        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableRow>
                <asp:TableCell ColSpan="2" Width="300" align="center"><asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab5_1_addusers.aspx">Назад</asp:HyperLink></asp:TableCell>
                <asp:TableCell ColSpan="2" Width="300" align="center"><asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab5_2_MyDefault.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>
    </div>
</asp:Content>