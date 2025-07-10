<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab5_3_Login.aspx.cs" Inherits="rwd_lab1.lab5_3_Login" %>

<%@ MasterType  virtualPath="~/Site.Master"%>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">
    <h1>Сегодня <% this.Response.Write(DateTime.Now.ToShortDateString()); %> г.</h1>
    <h2>Введите свои имя и пароль</h2>
    <table cellpadding="5" style="width: 100%">
        <tr>
            <td align="right" height="43" style="width: 167px">Имя пользователя:</td>
            <td><asp:TextBox ID="UsernameText" runat="server" /></td>
            <td>
                <asp:RequiredFieldValidator ID="UsernameRequiredValidator" runat="server" ControlToValidate="UsernameText" Display="Dynamic" ErrorMessage='Не заполнено поле "Имя пользователя"' ToolTip="Пустое поле ввода">*</asp:RequiredFieldValidator>
                <asp:RegularExpressionValidator ID="UsernameValidator" runat="server" ControlToValidate="UsernameText" Display="Dynamic" ErrorMessage="Неверное имя пользователя" ToolTip="Допустимы буквы, цифры, пробелы и подчеркивания" ValidationExpression="[а-яА-Я\w| ]*">*</asp:RegularExpressionValidator>
            </td>
        </tr>
        <tr>
            <td align="right" height="43" style="width: 167px">Пароль:</td>
            <td><asp:TextBox ID="PasswordText" runat="server" TextMode="Password" /></td>
            <td>
                <asp:RequiredFieldValidator ID="PwdRequiredValidator" runat="server" ControlToValidate="PasswordText" Display="Dynamic" ErrorMessage='Не заполнено поле "Пароль"' ToolTip="Пустое поле ввода">*</asp:RequiredFieldValidator>
                <asp:RegularExpressionValidator ID="PwdValidator" runat="server" ControlToValidate="PasswordText" Display="Dynamic" ErrorMessage="Неверный пароль" ToolTip="Используются недопустимые символы" ValidationExpression='[а-яА-Я\w| !"$&amp;/()=\-?\*]*'>*</asp:RegularExpressionValidator>
            </td>
        </tr>
    </table>
    <asp:Button ID="Button1" runat="server" Text="Отправить" OnClick="LoginAction_Click" />
    <div id="AuthResultWrapper" runat="server"></div>
    <asp:Label ID="lblResult" runat="server" />
    <asp:ValidationSummary ID="ValidationSummary1" runat="server" />

    <br />
    <br />
    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab5_2_MyDefault.aspx">Назад</asp:HyperLink></asp:TableCell>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab5_4_HashPasswords.aspx">Вперед</asp:HyperLink></asp:TableCell>
        </asp:TableRow>
    </asp:Table>
</asp:Content>









