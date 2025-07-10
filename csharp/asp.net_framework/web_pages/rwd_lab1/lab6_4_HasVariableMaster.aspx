<%@ Page Title="" Language="C#" MasterPageFile="~/lab6_1_masterpage.Master" AutoEventWireup="true" CodeBehind="lab6_4_HasVariableMaster.aspx.cs" Inherits="rwd_lab1.lab6_4_HasVariableMaster" %>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">

    <asp:Button OnClick="btn_ChangeMasterPage_Click" Text="Change Master Page" runat="server"/>

    <br />
    <br />
    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab6_3_Default2.aspx">Назад</asp:HyperLink>
                <asp:HyperLink ID="HyperLink1" runat="server" NavigateUrl="~/lab6_5_PageForNestedMaster.aspx">Вперед</asp:HyperLink>
            </asp:TableCell>
        </asp:TableRow>
    </asp:Table>

</asp:Content>
