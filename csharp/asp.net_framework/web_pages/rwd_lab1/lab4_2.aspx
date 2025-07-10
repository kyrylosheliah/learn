<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab4_2.aspx.cs" Inherits="rwd_lab1.lab4_2" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableHeaderRow>
                <asp:TableHeaderCell ColSpan="3" align="center"><h1 style="text-align:center">Обмен элементами в двух списках</h1></asp:TableHeaderCell>
            </asp:TableHeaderRow>
            <asp:TableRow>
                <asp:TableCell ColSpan="3" align="center">Выделите элементы в одном списке и перешлите в другой, используя кнопки</asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center" Width="300">
                    <asp:ListBox ID="ListBox1" runat="server" SelectionMode="Multiple" Width="100%"></asp:ListBox>
                </asp:TableCell>
                <asp:TableCell align="center" Width="300">
                    <asp:Button ID="Button1" runat="server" onClick="Button1_Click" Font-Bold="True" Font-Size="Large" Text="--&gt;" />
                    <br />
                    <asp:Button ID="Button2" runat="server" onClick="Button2_Click" Font-Bold="True" Font-Size="Large" Text="&lt;--" />
                </asp:TableCell>
                <asp:TableCell align="center" Width="300">
                    <asp:ListBox ID="ListBox2" runat="server" SelectionMode="Multiple" Width="100%"></asp:ListBox>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center"><asp:HyperLink ID="HyperLink4" runat="server" NavigateUrl="~/lab4.aspx">Назад</asp:HyperLink></asp:TableCell>
                <asp:TableCell align="center">&nbsp;</asp:TableCell>
                <asp:TableCell align="center"><asp:HyperLink ID="HyperLink2" runat="server" NavigateUrl="~/lab4_3.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>
    </div>
</asp:Content>