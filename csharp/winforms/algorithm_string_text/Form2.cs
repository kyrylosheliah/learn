using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp_lab9
{
	public partial class Form2 : Form
	{

		public Form2(Form1 toParent)
		{
			InitializeComponent();
			mainWindow = toParent;

			Refill();
		}

		private Form1 mainWindow;

		private void Refill()
		{
			label2.Text = string.Format("Словарь этой сессии: {0} элементов", mainWindow.dict.Count);
			listBox1.Items.Clear();
			if (mainWindow.dict.Count != 0)
			{
				listBox1.Items.AddRange(mainWindow.dict.ToArray());
			}
			else
			{
				listBox1.Items.Add("<ПУСТО>");
			}
		}

		private void Update(string toAdd)
		{
			mainWindow.dictAdd(toAdd);
		}

		private void UpdateThenRefill(string toAdd)
		{
			Update(toAdd);
			Refill();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			if (textBox1.Text.Length != 0)
			{
				UpdateThenRefill(textBox1.Text);
				label1.Text = "Слово добавлено";
			}
			else
			{
				label1.Text = "[!] Слово не введено";
			}
		}
	}
}
