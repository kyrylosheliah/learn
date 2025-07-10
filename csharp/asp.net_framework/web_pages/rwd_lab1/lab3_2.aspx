<%@ Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="lab3_2.aspx.cs" Inherits="rwd_lab1.lab3_2" %>

<asp:Content id="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <div align="center" id="ContentWrapper" runat="server">
        <asp:Table border="1" style="width:100%;" ID="Table1" runat="server">
            <asp:TableHeaderRow>
                <asp:TableHeaderCell ColSpan="2" align="center"><h1 style="text-align:center">Испытание переключателей</h1></asp:TableHeaderCell>
            </asp:TableHeaderRow>
            <asp:TableRow>
                <asp:TableCell align="center">Выберите артистов, которые Вам нравятся?</asp:TableCell>
                <asp:TableCell align="center">Кого из предложенных лиц Вы бы хотели видеть своим начальником?</asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center" Width="300">
                    <asp:CheckBoxList ID="CheckBoxList1" OnSelectedIndexChanged="ActorList_SelectedIndexChanged" runat="server" BackColor="#FFFF99" Font-Size="Large" Font-Strikeout="False" Font-Underline="False">
                        <asp:ListItem>Высоцкий</asp:ListItem>
                        <asp:ListItem>Галкин</asp:ListItem>
                        <asp:ListItem>Тимошенко</asp:ListItem>
                        <asp:ListItem>Куценко</asp:ListItem>
                        <asp:ListItem>Леонтьев</asp:ListItem>
                        <asp:ListItem>Смоктуновский</asp:ListItem>
                        <asp:ListItem>Пугачева</asp:ListItem>
                        <asp:ListItem>Пономарев</asp:ListItem>
                    </asp:CheckBoxList>
                </asp:TableCell>
                <asp:TableCell align="center" Width="300">
                    <asp:RadioButtonList ID="RadioButtonList1" OnSelectedIndexChanged="HeadList_SelectedIndexChanged" runat="server" BackColor="#FFFF99" Font-Size="Large">
                        <asp:ListItem>Абрамович</asp:ListItem>
                        <asp:ListItem>Порошенко</asp:ListItem>
                        <asp:ListItem>Ахметов</asp:ListItem>
                        <asp:ListItem>Тимошенко</asp:ListItem>
                        <asp:ListItem>Семенченко</asp:ListItem>
                        <asp:ListItem>Коломойский</asp:ListItem>
                        <asp:ListItem>Ющенко</asp:ListItem>
                        <asp:ListItem>Кучма</asp:ListItem>
                    </asp:RadioButtonList>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell Width="300">Список понравившихся артистов:</asp:TableCell>
                <asp:TableCell Width="300">Любимый начальник:</asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell style="background-color:#CCFFFF;">
                    <asp:Label ID="Actor" runat="server" Text="Actor"></asp:Label>
                </asp:TableCell>
                <asp:TableCell style="background-color:#CCFFFF;">
                    <asp:Label ID="Head" runat="server" Text="Head"></asp:Label>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center" ColSpan="2">
                    <asp:Button ID="Button" runat="server" Text="Отправить на обработку" />
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell align="center"><asp:HyperLink ID="HyperLink1" runat="server" NavigateUrl="~/lab3.aspx">Назад</asp:HyperLink></asp:TableCell>
                <asp:TableCell align="center"><asp:HyperLink ID="HyperLink2" runat="server" NavigateUrl="~/lab3_3.aspx">Вперед</asp:HyperLink></asp:TableCell>
            </asp:TableRow>
        </asp:Table>

    </div>
</asp:Content>