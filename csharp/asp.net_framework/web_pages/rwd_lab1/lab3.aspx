<%@ Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab3.aspx.cs" Inherits="rwd_lab1.lab3"%>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:Label ID="Title" runat="server" Text="Пусто" Font-Bold="True" Font-Size="X-Large" ForeColor="Red"></asp:Label>
        <br /><br />
        <asp:Label ID="Label2" runat="server" Text="Имя:"></asp:Label>
        <br /><br />
        <asp:TextBox ontextchanged="TextBox_TextChanged" ID="Name" runat="server" MaxLength="35" AutoPostBack="True" BorderStyle="Dotted" Width="200"></asp:TextBox>
        <br /><br />
        <asp:Label ID="Label3" runat="server" Text="Адрес:"></asp:Label>
        <br /><br />
        <asp:TextBox ontextchanged="TextBox_TextChanged" ID="Address" runat="server" TextMode="MultiLine" Text="Пусто" BackColor="Blue" ForeColor="Yellow" Font-Bold="True" AutoPostBack="True"></asp:TextBox>
        <br /><br />
        <asp:Button onclick="Button_Click" ID="Button" runat="server" Text="Submit Information" ToolTip="Показать сообщение" />
        <br /><br />
        <asp:Label ID="Result" runat="server" Text="Пусто" Font-Bold="True"></asp:Label>
        <br /><br />
        <hr />
        <asp:HyperLink ID="HyperLink1" runat="server" Text="Вперед" NavigateUrl="lab3_2.aspx"></asp:HyperLink>
    </div>
</asp:Content>