<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab5_8_DeleteUser.aspx.cs" Inherits="rwd_lab1.lab5_8_DeleteUser" %>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">

    <h2>Введите имя удаляемого пользователя</h2>
    <asp:Panel ID="MainPanel" runat="server" BorderColor="Silver"
        BorderStyle="Ridge"
        BorderWidth="2px" Height="90px" Width="412px">
        <table cellpadding="5" style="width: 100%">
            <tr>
                <td align="right" height="43" style="width: 167px">Имя&nbsp;пользователя:</td>
                <td>&nbsp;<asp:TextBox ID="username" runat="server" />
                </td>
            </tr>
        </table>
        <asp:Button ID="Button1" runat="server" Text="Удалить"
            OnClick="DeleteUser_Click" />
    </asp:Panel>
    <asp:Label ID="lblResult" runat="server" Font-Bold="True"
        Font-Size="Large" ForeColor="Blue">
    </asp:Label>



    <br />
    <br />
    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab5_7_Register.aspx">Назад</asp:HyperLink></asp:TableCell>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab5_9_UserList.aspx">Вперед</asp:HyperLink></asp:TableCell>
        </asp:TableRow>
    </asp:Table>

</asp:Content>

