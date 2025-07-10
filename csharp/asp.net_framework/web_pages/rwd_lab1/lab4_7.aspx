<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab4_7.aspx.cs" Inherits="rwd_lab1.lab4_7" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:DataList ID="DataList2" runat="server" BackColor="White" BorderColor="White" BorderStyle="Ridge" BorderWidth="2px" CellPadding="3" CellSpacing="1">
            <FooterStyle BackColor="#C6C3C6" ForeColor="Black" />
            <ItemStyle BackColor="#DEDFDE" ForeColor="Black" />
            <SelectedItemStyle BackColor="#9471DE" Font-Bold="True" ForeColor="White" />
            <HeaderStyle BackColor="#4A3C8C" Font-Bold="True" ForeColor="#E7E7FF" />
            <HeaderTemplate>
                <table border="1" style="width:100%;">
                    <tr><td colspan="4">Exams</td></tr>
                    <tr>
                        <td align="center"><strong>id</strong></td>
                        <td align="center"><strong>full_name</strong></td>
                        <td align="center"><strong>lesson_id</strong></td>
                        <td align="center"><strong>grade</strong></td>
                    </tr>
            </HeaderTemplate>
            <ItemTemplate>
                <tr>
                    <td align="left"><%# Eval("id") %></td>
                    <td align="left"><%# Eval("full_name") %></td>
                    <td align="left"><%# Eval("lesson_id") %></td>
                    <td align="left"><%# Eval("grade") %></td>
                </tr>
            </ItemTemplate>
            <FooterTemplate></table></FooterTemplate>
        </asp:DataList>

        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableRow>
                <asp:TableCell ColSpan="2" Width="300" align="center"><asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab4_6.aspx">Назад</asp:HyperLink></asp:TableCell>
                <asp:TableCell ColSpan="2" Width="300" align="center"><asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab4.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>
    </div>
</asp:Content>