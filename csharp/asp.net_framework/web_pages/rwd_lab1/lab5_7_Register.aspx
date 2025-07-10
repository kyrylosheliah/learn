<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab5_7_Register.aspx.cs" Inherits="rwd_lab1.lab5_7_Register" %>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">

    <h3>Create New User</h3>  
    <br />
    <table cellpadding="3" border="0">  
        <tr>  
            <td></td>  
            <td colspan="2"><b>Sign Up for New User Account</b></td>  
        </tr>  
        <tr>  
            <td>UserName:</td>  
            <td><asp:TextBox ID="txtUserName" runat="server"/></td>  
            <td><asp:RequiredFieldValidator ID="Register_rqfUserName" runat="server" ControlToValidate="txtUserName" Display="Dynamic" ErrorMessage="Required" ForeColor="Red"/></td>  
        </tr>  
        <tr>  
            <td>Password:</td>  
            <td><asp:TextBox ID="txtPwd" runat="server" TextMode="Password"/></td>  
            <td><asp:RequiredFieldValidator ID="Register_RequiredFieldValidator1" runat="server" ControlToValidate="txtPwd" Display="Dynamic" ErrorMessage="Required" ForeColor="Red"/></td>  
        </tr>  
        <tr>  
            <td>Confirm Password:</td>  
            <td><asp:TextBox ID="txtCnfPwd" runat="server" TextMode="Password"/></td>  
            <td>
                <asp:RequiredFieldValidator id="Register_PasswordConfirmRequiredValidator" runat="server" ControlToValidate="txtCnfPwd" ForeColor="red" Display="Dynamic" ErrorMessage="Required" />  
                <asp:CompareValidator id="Register_PasswordConfirmCompareValidator" runat="server" ControlToValidate="txtCnfPwd" ForeColor="red" Display="Dynamic" ControlToCompare="txtPwd" ErrorMessage="Confirm password must match password." />  
            </td>  
        </tr>  
        <tr>  
            <td>Email:</td>  
            <td><asp:TextBox ID="txtEmail" runat="server"/></td>  
            <td><asp:RequiredFieldValidator ID="Register_RequiredFieldValidator3" runat="server" ControlToValidate="txtEmail" Display="Static" ErrorMessage="Required" ForeColor="Red"/></td>  
        </tr>  
        <tr>  
            <td>Security Question:</td>  
            <td><asp:TextBox ID="txtQuestion" runat="server"/></td>  
            <td><asp:RequiredFieldValidator ID="Register_RequiredFieldValidator4" runat="server" ControlToValidate="txtQuestion" Display="Static" ErrorMessage="Required" ForeColor="Red"/></td>  
        </tr>  
        <tr>  
            <td>Security Answer:</td>  
            <td><asp:TextBox ID="txtAnswer" runat="server"/></td>  
            <td><asp:RequiredFieldValidator ID="Register_RequiredFieldValidator5" runat="server" ControlToValidate="txtAnswer" Display="Static" ErrorMessage="Required" ForeColor="Red"/></td>  
        </tr>  
        <tr>  
            <td></td>  
            <td><asp:Button ID="btnSubmit" runat="server" Text="Create User" onclick="RegisterAction_Click" /></td>  
        </tr>  
        <tr>  
            <td colspan="3"><asp:Label ID="Label1" runat="server" Font-Bold="true"/></td>
        </tr>  
    </table>
        <asp:Label ID="RegistrationResult" runat="server" />



    <br />
    <br />
    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab5_6_Login.aspx">Назад</asp:HyperLink></asp:TableCell>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab5_8_DeleteUser.aspx">Вперед</asp:HyperLink></asp:TableCell>
        </asp:TableRow>
    </asp:Table>

</asp:Content>
