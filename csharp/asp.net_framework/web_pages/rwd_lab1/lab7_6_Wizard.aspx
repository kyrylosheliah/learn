<%@ Page Title="" Language="C#" MasterPageFile="~/lab7_2_navigationmaster.Master" AutoEventWireup="true" CodeBehind="lab7_6_Wizard.aspx.cs" Inherits="rwd_lab1.lab7_6_Wizard" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">

    <asp:Wizard DisplaySideBar="true"
        CancelButtonText="CANCEL"
        StartNextButtonText=">>>"
        StepPreviousButtonText="<<<"
        StepNextButtonText=">>>"
        FinishPreviousButtonText="<<<"
        FinishCompleteButtonText="COMPLETE"
        ActiveStepIndex="0" runat="server">
        <WizardSteps>
            <asp:WizardStep ID="Step1">
                <table>
                    <tr>
                        <td>e-mail</td>
                        <td>
                            <input type="email" /></td>
                    </tr>
                    <tr>
                        <td>password</td>
                        <td>
                            <input type="password" /></td>
                    </tr>
                    <tr>
                        <td>re-password</td>
                        <td>
                            <input type="password" /></td>
                    </tr>
                </table>
            </asp:WizardStep>
            <asp:WizardStep  ID="Step2">
                <table>
                    <tr>
                        <td>Control Question</td>
                        <td>
                            <input type="text" /></td>
                    </tr>
                    <tr>
                        <td>Answer</td>
                        <td>
                            <input type="text" /></td>
                    </tr>
                    <tr>
                        <td>Backup e-mail</td>
                        <td>
                            <input type="email" /></td>
                    </tr>
                </table>
            </asp:WizardStep>
            <asp:WizardStep  ID="Step3">
                <table>
                    <tr>
                        <td>FName</td>
                        <td>
                            <input type="text" /></td>
                    </tr>
                    <tr>
                        <td>LName</td>
                        <td>
                            <input type="text" /></td>
                    </tr>
                    <tr>
                        <td>Date-Of-Birth</td>
                        <td>
                            <input type="text" /></td>
                    </tr>
                    <tr>
                        <td>Sex</td>
                        <td>
                            <fieldset>
                                <div>
                                    <input  type="radio" id="Sex_Male" name="Sex" value="Male">
                                    Male
                                </div>
                                <div>
                                    <input type="radio" id="Sex_Female" name="Sex" value="Female">
                                    Female
                                </div>
                            </fieldset>
                        </td>
                    </tr>
                </table>
            </asp:WizardStep>
        </WizardSteps>
        <StepNavigationTemplate>
            <asp:Button ID="StepPreviousButton" runat="server" CausesValidation="False" CommandName="MovePrevious" />
            <asp:Button ID="StepNextButton" runat="server" CommandName="MoveNext" />
        </StepNavigationTemplate>
    </asp:Wizard>

</asp:Content>