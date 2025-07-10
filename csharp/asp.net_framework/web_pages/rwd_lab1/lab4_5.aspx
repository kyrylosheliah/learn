<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab4_5.aspx.cs" Inherits="rwd_lab1.lab4_5" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableRow>
                <asp:TableCell ColSpan="2" align="center">
                    <h1>Lessons</h1>
                    <br><br>
                    <asp:DataList ID="DataList2" runat="server" BackColor="White" BorderColor="White" BorderStyle="Ridge" BorderWidth="2px" CellPadding="3" CellSpacing="1">
                           <FooterStyle BackColor="#C6C3C6" ForeColor="Black" />
                           <ItemStyle BackColor="#DEDFDE" ForeColor="Black" />
                           <SelectedItemStyle BackColor="#9471DE" Font-Bold="True" ForeColor="White" />
                           <HeaderStyle BackColor="#4A3C8C" Font-Bold="True" ForeColor="#E7E7FF" />
                           <ItemTemplate>
                               id: <asp:Label ID="idLabel" runat="server" Text='<%# Eval("id") %>' />
                               <br />
                               Title: <asp:Label ID="TitleLabel" runat="server" Text='<%# Eval("Title") %>' />
                               <br />
                               Teacher: <asp:Label ID="TeacherLabel" runat="server" Text='<%# Eval("Teacher") %>' />
                               <br />
                               Type: <asp:Label ID="TypeLabel" runat="server" Text='<%# Eval("Type") %>' />
                               <hr />
                           </ItemTemplate>
                    </asp:DataList>    
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell Width="300" align="center"><asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab4_4.aspx">Назад</asp:HyperLink></asp:TableCell>
                <asp:TableCell Width="300" align="center"><asp:HyperLink ID="HyperLink3" runat="server" NavigateUrl="~/lab4_6.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>
    </div>
</asp:Content>