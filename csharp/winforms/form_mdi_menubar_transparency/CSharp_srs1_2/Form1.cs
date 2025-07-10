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

namespace CSharp_srs1_2
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

		private void Form1_Load(object sender, EventArgs e)
		{
			GraphicsPath myPath = new GraphicsPath();
			myPath.AddPolygon(new Point[] {
				new Point(0, 0),
				new Point(0, Height),
				new Point(Width, 0)
			});
			Region myRegion = new Region(myPath);
			Region = myRegion;
		}

		private Point downPoint = Point.Empty;

		public void Form1_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				downPoint = new Point(e.X, e.Y);
			}
		}

		public void Form1_MouseMove(object sender, MouseEventArgs e)
		{
			if (downPoint != Point.Empty)
			{
				Location = new Point(Left + e.X - downPoint.X, Top + e.Y - downPoint.Y);
			}
		}

		public void Form1_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				downPoint = Point.Empty;
			}
		}
	}
}
