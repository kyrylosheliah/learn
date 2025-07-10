<%@ Title="lab2_2" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab2_2.aspx.cs" Inherits="rwd_lab1.lab2_2"%>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <br />
    <br />
    <center>
        <samp align="center" id="sampID" runat="server">HTML Button</samp>
        <br />
        <br />
        <input id="Message1" runat="server" type="button"
                value="Текст1" onserverclick="Message1_ServerClick">
        &nbsp;&nbsp;&nbsp; 
        <input id="Message2" runat="server" type="button"
                value="Текст2" onserverclick="Message2_ServerClick">
        <br />
        <a id="PrevLink" runat="server">Назад</a> 
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
        <a id="NextLink" runat="server">Вперед</a>
    </center>
</asp:Content>