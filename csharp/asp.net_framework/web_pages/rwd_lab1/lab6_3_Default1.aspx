<%@ Page Title="Пример обращения к мастер-странице" Language="C#" MasterPageFile="~/lab6_1_masterpage.Master" AutoEventWireup="true" CodeBehind="lab6_3_Default1.aspx.cs" Inherits="rwd_lab1.lab6_3_Default1" %>

<%@ MasterType virtualPath="~/lab6_1_masterpage.Master"%>

<asp:Content ID="BodyContent" align="center" ContentPlaceHolderID="MainContent" runat="server">

    <h1>Default1</h1>

    <p>Should have one title.</p>

    <br />
    <br />
    <asp:Table border="1" Style="width: 100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell ColSpan="2" Width="300" align="center">
                <asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab6_2_TestContent.aspx">Назад</asp:HyperLink>
                <asp:HyperLink ID="HyperLink1" runat="server" NavigateUrl="~/lab6_3_Default2.aspx">Вперед</asp:HyperLink>
            </asp:TableCell>
        </asp:TableRow>
    </asp:Table>

</asp:Content>


