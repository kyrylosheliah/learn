<%@ Title="lab1" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab1.aspx.cs" Inherits="rwd_lab1.lab1"%>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <br />
    <br />
    <asp:Label ID="MessageLabel" runat="server" Text="Початкове значення текстової мітки" ForeColor="Blue" Font-Bold="True" Font-Size="Large"></asp:Label>
    <br />
    <br />
    <asp:Button ID="ReplaceButton" runat="server" OnClick="ReplaceButton_Click" Text="Змінити текст" ForeColor="Blue" Font-Bold="True" />
</asp:Content>