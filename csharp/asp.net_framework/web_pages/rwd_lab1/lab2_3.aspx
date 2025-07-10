<%@ Title="lab2_3" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab2_3.aspx.cs" Inherits="rwd_lab1.lab2_3"%>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div id="ContentWrapper" runat="server">
    <h1 align="center">HTMLGenericControl</h1>
    <center>
        <p>Блок изменения цвета фона страницы</p>
        <p>
            <samp>Цвет фона:</samp>
            <select id="PageColor" runat="server">
                <option selected value="bg-light">bg-light</option>
                <option value="bg-dark">bg-dark</option>
                <option value="bg-info">bg-info</option>
                <option value="bg-warning">bg-warning</option>
                <option value="bg-danger">bg-danger</option>
                <option value="bg-success">bg-success</option>
                <option value="bg-white">bg-white</option>
            </select>
        </p>
        <p><input id="ColorButton" runat="server" type="submit" value="Изменить цвет фона" onserverclick="ColorButton_ServerClick"/></p>
        <hr>
        <font id="FontID" runat="server">Текстовая метка переменного размера</font>
        <p>
            <samp>
                Размер текста:
            </samp>
            <select id="FontSize" runat="server" name="FontSize">
                <option selected value="1">Small</option>
                <option value="2">Medium</option>
                <option value="4">Large</option>
                <option value="5">Extra Large</option>
            </select>
        </p>
        <p><input id="SizeButton" runat="server" type="submit" value="Изменить размер шрифта" onserverclick="SizeButton_ServerClick"/></p>
        <hr>
        <p>Программирование тега параграфа</p>
        <p id="Text0" runat="server">Нажмите на кнопку и сервер добавит две новых строки</p>
        <p id="Text1" runat="server"></p>
        <p id="Text2" runat="server"></p>
        <p><input id="AddButton" runat="server" type="submit" value="Добавить строки" onserverclick="AddButton_ServerClick"/></p>
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