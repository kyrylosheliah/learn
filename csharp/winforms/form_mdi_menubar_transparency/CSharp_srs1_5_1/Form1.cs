using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace CSharp_srs1_5_1
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			Close();
		}

		public Point downPoint = Point.Empty;

		private void Form1_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				downPoint = new Point(e.X, e.Y);
			}
		}

		private void Form1_MouseMove(object sender, MouseEventArgs e)
		{
			if (downPoint != Point.Empty)
			{
				Location = new Point(Left + e.X - downPoint.X, Top + e.Y - downPoint.Y);
			}
		}

		private void Form1_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				downPoint = Point.Empty;
			}
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			GraphicsPath myPath = new GraphicsPath();
			myPath.AddEllipse(0, 0, Width, Height);
			Region myRegion = new Region(myPath);
			Region = myRegion;
		}
	}
}
