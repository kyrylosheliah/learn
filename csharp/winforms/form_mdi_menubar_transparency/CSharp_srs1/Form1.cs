using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp_srs1
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			if (FormBorderStyle == FormBorderStyle.Fixed3D)
			{
				FormBorderStyle = FormBorderStyle.Sizable;
			}
			else
			{
				FormBorderStyle = FormBorderStyle.Fixed3D;
			}
		}

		private void button2_Click(object sender, EventArgs e)
		{
			if (Size.Width == 300 && Size.Height == 100)
			{
				Size = new Size(400, 500);
			}
			else
			{
				Size = new Size(300, 100);
			}
		}

		private void button3_Click(object sender, EventArgs e)
		{
			if (Opacity == 0.75)
			{
				Opacity = 1;
			}
			else
			{
				Opacity = 0.75;
			}
		}
	}
}
