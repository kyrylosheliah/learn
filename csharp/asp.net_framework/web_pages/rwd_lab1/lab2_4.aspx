<%@ Title="lab2_4" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab2_4.aspx.cs" Inherits="rwd_lab1.lab2_4"%>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div id="ContentWrapper" runat="server">
    <h1 align="center">HTMLGenericControl</h1>
    <center>
        <h2 align="center">Управление элементом HTMLImage</h2>
        <font color="red"><p id="PictureTitle" runat="server" /></font>
        <img id="Image" runat="server" />
        <p></p>
        <samp>Выберите рисунок:</samp>
        <select id="SelectPicture" runat="server" >
            <option selected value="1">Первый рисунок</option>
            <option value="2">Второй рисунок</option>
            <option value="3">Третий рисунок</option>
        </select>
        <p><input id="PictureButton" runat="server" type="submit" value="Загрузить рисунок" onserverclick="PictureButton_ServerClick"/></p>
        <hr>
        <a id="PrevLink" runat="server">Назад</a> 
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
        <a id="NextLink" runat="server">Вперед</a>
    </center>

    <br />
    <br />
    <a id="PageLink" runat="server">-> lab2</a>

    </div>
</asp:Content>