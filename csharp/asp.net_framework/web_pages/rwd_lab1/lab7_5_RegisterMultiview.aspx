<%@ Page Title="" Language="C#" MasterPageFile="~/lab7_2_navigationmaster.Master" AutoEventWireup="true" CodeBehind="lab7_5_RegisterMultiview.aspx.cs" Inherits="rwd_lab1.lab7_5_RegisterMultiview" %>
<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">

    <asp:MultiView ID="User_Registration" OnActiveViewChanged="User_Registration_ActiveViewChanged" runat="server">
        <asp:View ID="Registration" runat="server">
            <table>
                <tr>
                    <td>e-mail</td>
                    <td><input type="email"/></td>
                </tr>
                <tr>
                    <td>password</td>
                    <td><input type="password"/></td>
                </tr>
                <tr>
                    <td>re-password</td>
                    <td><input type="password"/></td>
                </tr>
                <tr>
                    <td align="center">&nbsp;</td>
                    <td align="center"><asp:Button Text=" >>> " onclick="User_Registration_Next" runat="server" /></td>
                </tr>
            </table>
        </asp:View>
        <asp:View ID="Control_Question" runat="server">
            <table>
                <tr>
                    <td>Control Question</td>
                    <td><input type="text"/></td>
                </tr>
                <tr>
                    <td>Answer</td>
                    <td><input type="text"/></td>
                </tr>
                <tr>
                    <td>Backup e-mail</td>
                    <td><input type="email"/></td>
                </tr>
                <tr>
                    <td align="center"><asp:Button Text=" <<< " onclick="User_Registration_Prev" runat="server" /></td>
                    <td align="center"><asp:Button Text=" >>> " onclick="User_Registration_Next" runat="server" /></td>
                </tr>
            </table>
        </asp:View>
        <asp:View ID="Additional_Info" runat="server">
            <table>
                <tr>
                    <td>FName</td>
                    <td><input type="text"/></td>
                </tr>
                <tr>
                    <td>LName</td>
                    <td><input type="text"/></td>
                </tr>
                <tr>
                    <td>Date-Of-Birth</td>
                    <td><input type="text"/></td>
                </tr>
                <tr>
                    <td>Sex</td>
                    <td>
                        <fieldset>
                            <div>
                                <input type="radio" id="Sex_Male" name="Male" value="Male"> Male
                            </div>
                            <div>
                                <input type="radio" id="Sex_Female" name="Female" value="Female"> Female
                            </div>
                        </fieldset>
                    </td>
                </tr>
                <tr>
                    <td align="center"><asp:Button Text=" <<< " onclick="User_Registration_Prev" runat="server" /></td>
                    <td align="center">&nbsp;</td>
                </tr>
            </table>
        </asp:View>
    </asp:MultiView>
    <asp:DropDownList OnSelectedIndexChanged="DropDownList1_SelectedIndexChanged" ID="DropDownList1" runat="server" AutoPostBack="true"></asp:DropDownList>
</asp:Content>
