<%@ Page Title="" Language="C#" MasterPageFile="~/lab6_5_masterpagenested.master" AutoEventWireup="true" CodeBehind="lab6_5_PageForNestedMaster.aspx.cs" Inherits="rwd_lab1.lab6_5_PageForNestedMaster" %>

<asp:Content ID="Content1" ContentPlaceHolderID="MainContent_Nested" Runat="Server">
    <h3>Text inside Content Page with Nested Master</h3>

    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab6_4_HasVariableMaster.aspx">Назад</asp:HyperLink>
                <asp:HyperLink ID="HyperLink1" runat="server" NavigateUrl="~/lab6_2_TestContent.aspx">Вперед</asp:HyperLink>
            </asp:TableCell>
        </asp:TableRow>
    </asp:Table>
</asp:Content>
