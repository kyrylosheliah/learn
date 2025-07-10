using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Web;
using System.Web.Optimization;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace rwd_lab1
{
    public partial class lab5_7_Register : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }


        protected void RegisterAction_Click(Object sender, EventArgs e)
        {
            MembershipCreateStatus createStatus;
            MembershipUser user = Membership.CreateUser(txtUserName.Text, txtPwd.Text, txtEmail.Text, txtQuestion.Text, txtAnswer.Text, true, out createStatus);
            switch (createStatus)
            {
                //This Case Occured whenver User Created Successfully in database  
                case MembershipCreateStatus.Success:
                    RegistrationResult.ForeColor = Color.Green;
                    RegistrationResult.Text = "The user account was successfully created";
                    txtUserName.Text = string.Empty;
                    txtEmail.Text = string.Empty;
                    txtQuestion.Text = string.Empty;
                    txtAnswer.Text = string.Empty;
                    break;
                // This Case Occured whenver we send duplicate UserName  
                case MembershipCreateStatus.DuplicateUserName:
                    RegistrationResult.ForeColor = Color.Red;
                    RegistrationResult.Text = "The user with the same UserName already exists!";
                    break;
                //This Case Occured whenver we give duplicate mail id  
                case MembershipCreateStatus.DuplicateEmail:
                    RegistrationResult.ForeColor = Color.Red;
                    RegistrationResult.Text = "The user with the same email address already exists!";
                    break;
                //This Case Occured whenver we send invalid mail format  
                case MembershipCreateStatus.InvalidEmail:
                    RegistrationResult.ForeColor = Color.Red;
                    RegistrationResult.Text = "The email address you provided is invalid.";
                    break;
                //This Case Occured whenver we send empty data or Invalid Data  
                case MembershipCreateStatus.InvalidAnswer:
                    RegistrationResult.ForeColor = Color.Red;
                    RegistrationResult.Text = "The security answer was invalid.";
                    break;
                // This Case Occured whenver we supplied weak password  
                case MembershipCreateStatus.InvalidPassword:
                    RegistrationResult.ForeColor = Color.Red;
                    RegistrationResult.Text = "The password you provided is invalid. It must be 7 characters long and have at least 1 special character.";
                    break;
                default:
                    RegistrationResult.ForeColor = Color.Red;
                    RegistrationResult.Text = "There was an unknown error; the user account was NOT created.";
                    break;
            }
        }
    }
}