<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab2_5.aspx.cs" Inherits="rwd_lab1.lab2_5" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div id="ContentWrapper" runat="server">
    <h1 align="center">HTMLGenericControl</h1>
    <center>
        <p>
            <br />
            <strong align="center">input type="button"</strong>
            <br />
            <input type="button" name="i1" value="input type='button'" />
        </p>
        <p>
            <br />
            <strong align="center">input type="checkbox"</strong>
            <br />
            <input type="checkbox" name="i2" value="" />
        </p>
        <p>
            <br />
            <strong align="center">input type="file"</strong>
            <br />
            <input type="file" name="i3" value="" />
        </p>
        <p>
            <br />
            <strong align="center">input type="hidden"</strong>
            <br />
            <input type="hidden" name="i4" value="" />
        </p>
        <p>
            <br />
            <strong align="center">input type="image"</strong>
            <br />
            <input type="image" name="i5" src="/Images/button.png" />
        </p>
        <p>
            <br />
            <strong align="center">input type="radio"</strong>
            <br />
            <input type="radio" name="i6" value="" />
        </p>
        <p>
            <br />
            <strong align="center">input type="text"</strong>
            <br />
            <input type="text" name="i7" value="" />
        </p>
        <p>
            <br />
            <strong align="center">select</strong>
            <br />
            <select>
                <option value="value1">text1</option>
                <option value="value2">text2</option>
                <option value="value3">text3</option>
                <option value="value4">text4</option>
                <option value="value5">text5</option>
            </select>
        </p>
        <p>
            <br />
            <strong align="center">asp:Table > asp:TableRow > asp:TableCell</strong>
            <br />
            <asp:Table runat="server">
                <asp:TableHeaderRow>
                    <asp:TableHeaderCell>HeaderCell</asp:TableHeaderCell>
                    <asp:TableHeaderCell>HeaderCell</asp:TableHeaderCell>
                </asp:TableHeaderRow>
                <asp:TableRow>
                    <asp:TableCell>TableCell</asp:TableCell>
                    <asp:TableCell>TableCell</asp:TableCell>
                </asp:TableRow>
                <asp:TableFooterRow>
                    <asp:TableCell>TableCellInsideFooterRow</asp:TableCell>
                    <asp:TableCell>TableCellInsideFooterRow</asp:TableCell>
                </asp:TableFooterRow>
            </asp:Table>
        </p>
        <p>
            <br />
            <strong align="center">textarea</strong>
            <br />
            <textarea></textarea>
        </p>
        
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