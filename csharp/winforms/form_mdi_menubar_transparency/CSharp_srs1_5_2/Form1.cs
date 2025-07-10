using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp_srs1_5_2
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			WindowState = FormWindowState.Normal;
			FormBorderStyle = FormBorderStyle.None;
			Bounds = Screen.PrimaryScreen.Bounds;
		}

		private void Form1_Click(object sender, EventArgs e)
		{
			Hide();
			Form2 form = new Form2();
			form.Closed += (s, args) => this.Close();
			form.Show();
		}
	}
}
