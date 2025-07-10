<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab5_10_UpdateUser.aspx.cs" Inherits="rwd_lab1.lab5_10_UpdateUser" %>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">


    <h2>
        <asp:Label ID="lblUsersList" runat="server" Font-Bold="true"
            Text="Список зарегистрированных пользователей"></asp:Label>
    </h2>
    <asp:GridView ID="UsersGridView" runat="server"
        DataKeyNames="UserName"
        AutoGenerateColumns="False"
        OnSelectedIndexChanged="UsersGridView_SelectedIndexChanged">
        <Columns>
            <asp:BoundField DataField="UserName" HeaderText="Имя" />
            <asp:BoundField DataField="Email" HeaderText="email" />
            <asp:BoundField DataField="CreationDate" HeaderText="Создан" />
            <asp:CommandField ShowSelectButton="True" HeaderText="Детали"
                SelectText="Показать" />
        </Columns>
    </asp:GridView>
    <h2>
        <asp:Label ID="lblUser" runat="server"
            Text="Подробности для выделенного пользователя"
            Visible="False" Font-Bold="true"></asp:Label>
    </h2>
    <table id="tableDetails" bordercolor="#0000FF"
        runat="server">
        <tr>
            <td width="50%">Пользователь:</td>
            <td>
                <asp:Label ID="lblUserName" runat="server"></asp:Label></td>
        </tr>
        <tr>
            <td width="50%">
                <font>email:</font></td>
            <td>
                <asp:TextBox ID="txtEmail" runat="server">
                </asp:TextBox>
                <asp:RequiredFieldValidator
                    ID="RequiredFieldValidator1" runat="server"
                    ControlToValidate="txtEmail" Display="Dynamic">*
                </asp:RequiredFieldValidator>
                <asp:RegularExpressionValidator ID="RegularExpressionValidator1"
                    runat="server" ControlToValidate="txtEmail"
                    Display="Dynamic"
                    ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*">*
                </asp:RegularExpressionValidator></td>
        </tr>
        <tr>
            <td width="50%">Контрольный вопрос:</td>
            <td>
                <asp:Label ID="lblPasswordQuestion" runat="server"></asp:Label></td>
        </tr>
        <tr>
            <td width="50%">Дата последней регистрации:</td>
            <td>
                <asp:Label ID="lblLastLoginDate" runat="server"></asp:Label></td>
        </tr>
        <tr>
            <td width="50%">
                <font>Комментарии:</font></td>
            <td>
                <asp:TextBox ID="txtComment" runat="server" TextMode="MultiLine"></asp:TextBox></td>
        </tr>
        <tr>
            <td width="50%">
                <font>Проверенный:</font></td>
            <td>
                <asp:CheckBox ID="checkIsApproved" runat="server" /></td>
        </tr>
        <tr>
            <td width="50%">Заблокирован:</td>
            <td>
                <asp:CheckBox ID="checkIsLockedOut" runat="server" /></td>
        </tr>
        <tr>
            <td colspan="2" align="center">
                <asp:Button ID="btnUpdate" runat="server" Text="Обновить"
                    OnClick="btnUpdate_Click" /></td>
        </tr>
    </table>




    <br />
    <br />
    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab5_9_UserList.aspx">Назад</asp:HyperLink></asp:TableCell>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab5_1_addusers.aspx">Вперед</asp:HyperLink></asp:TableCell>
        </asp:TableRow>
    </asp:Table>

</asp:Content>

