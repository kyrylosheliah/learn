<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab3_3.aspx.cs" Inherits="rwd_lab1.lab3_3" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
        <asp:TableRow>
            <asp:TableCell Width="300">
                <asp:DropDownList id="DropDownList1" OnSelectedIndexChanged="DropDownList_SelectedIndexChanged" OnDataBinding="DropDownList_SelectedIndexChanged" runat="server" AutoPostBack="True">
                    <asp:listitem text="text1" Value="1" />
                    <asp:listitem text="text2" Value="2" />
                    <asp:listitem text="text3" Value="3" />
                    <asp:listitem text="text4" Value="4" />
                </asp:DropDownList>
            </asp:TableCell>
            <asp:TableCell Width="300">
                <div id="DropDownList_Managable" runat="server">
                    ___
                </div>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell Width="300">
                <asp:ListBox id="ListBox1" OnSelectedIndexChanged="ListBox_SelectedIndexChanged" SelectionMode="Multiple" runat="server" AutoPostBack="True">
                    <asp:listitem text="text1text1text1" Value="1" />
                    <asp:listitem text="text2text2text2" Value="2" />
                    <asp:listitem text="text3text3text3" Value="3" />
                    <asp:listitem text="text4text4text4" Value="4" />
                    <asp:listitem text="text5text5text5" Value="5" />
                    <asp:listitem text="text6text6text6" Value="6" />
                    <asp:listitem text="text7text7text7" Value="7" />
                    <asp:listitem text="text8text8text8" Value="8" />
                </asp:ListBox>
            </asp:TableCell>
            <asp:TableCell Width="300">
                <div id="ListBox_Managable" runat="server">
                    ___
                </div>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell Width="300">
                <asp:AdRotator id="AdRotator1" runat="server"></asp:AdRotator>
            </asp:TableCell>
            <asp:TableCell Width="300">
                <asp:Button OnClick="AdRotator_Managable" id="UploadUpdateButton" Text="Update" runat="server" />
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell Width="300">
                <asp:Calendar ID="Calendar1" OnSelectionChanged="Calendar_SelectionChanged" runat="server" AutoPostBack="True"></asp:Calendar>
            </asp:TableCell>
            <asp:TableCell Width="300">
                <div id="Calendar_Managable" runat="server">
                    ___
                </div>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell align="center">
                <asp:HyperLink id="HyperLink1" runat="server" NavigateUrl="~/lab3_2.aspx">Назад</asp:HyperLink>
            </asp:TableCell>
            <asp:TableCell align="center">
                <asp:HyperLink id="HyperLink2" runat="server" NavigateUrl="~/lab3.aspx">Вперед</asp:HyperLink>
            </asp:TableCell>
        </asp:TableRow>
    </asp:Table>
</asp:Content>

