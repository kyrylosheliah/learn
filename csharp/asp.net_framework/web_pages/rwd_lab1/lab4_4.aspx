<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab4_4.aspx.cs" Inherits="rwd_lab1.lab4_4" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableRow>
                <asp:TableCell ColSpan="2" align="center">
                    <asp:DataGrid ID="GridView1" runat="server" BackColor="White" BorderColor="White" BorderStyle="Ridge" BorderWidth="2px" CellPadding="3" CellSpacing="1" GridLines="None" >
                        <FooterStyle BackColor="#C6C3C6" ForeColor="Black" />
                        <SelectedItemStyle BackColor="#9471DE" Font-Bold="True" ForeColor="White" />
                        <PagerStyle BackColor="#C6C3C6" ForeColor="Black" HorizontalAlign="Right" />
                        <ItemStyle BackColor="#DEDFDE" ForeColor="Black" />
                        <HeaderStyle BackColor="#4A3C8C" Font-Bold="True" ForeColor="#E7E7FF" />
                    </asp:DataGrid>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell Width="300" align="center"><asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab4_3.aspx">Назад</asp:HyperLink></asp:TableCell>
                <asp:TableCell Width="300" align="center"><asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab4_5.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>
    </div>
</asp:Content>