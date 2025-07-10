using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharp_lab1
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			try
			{
				double sum = Convert.ToDouble(textBox3.Text);
				double d = Convert.ToDouble(textBox4.Text);
				int n = Convert.ToInt32(textBox5.Text);
				sum += n * d;
				textBox6.Text = Convert.ToString(sum);
			}
			catch
			{
				textBox6.Text = "ОШИБКА входных значений";
			}
		}

		private void label1_MouseHover(object sender, EventArgs e)
		{
			label1.Text = "2. Напишіть обробник\n події, коли при\n русі мишки над\n міткою, текст,\n розташований в мітці,\n набуває вигляду\n конкретного завдання.";
			label1.Font = new Font(label1.Font.Name, 10.25f, FontStyle.Bold);
			label1.ForeColor = ColorTranslator.FromHtml("#FF0000");
		}

		private void label1_MouseLeave(object sender, EventArgs e)
		{
			label1.Text = "Працює мишка";
			label1.Font = new Font(label1.Font.Name, 8.25f, FontStyle.Regular);
			label1.ForeColor = ColorTranslator.FromHtml("#000000");
		}

		private void button1_Click(object sender, EventArgs e)
		{
			try
			{
				var Today = DateTime.Today;
				label10.Text = String.Format("Текущий год: {0}\nВы", Today.Year) + ((Convert.ToBoolean(textBox1.Text.Length))?(", "+ textBox1.Text+",") :("")) +String.Format(" родились в {0} году", Today.Year - Convert.ToInt32(textBox2.Text));
			}
			catch
			{
				label10.Text = "ОШИБКА\nВозраст введен неверно";
			}
		}

		private void button3_Click(object sender, EventArgs e)
		{
			bool digitFlag = false;
			foreach (char character in textBox7.Text)
			{
				if (!Char.IsDigit(character))
				{
					digitFlag = true;
				}
			}
			if (digitFlag)
			{
				label9.Text = "ОШИБКА входного значения";
				return;
			}

			if (textBox7.Text.Length == 3)
			{
				char charMemory = textBox7.Text[0];
				bool equalityFlag = true;
				for (int i = 1; i < textBox7.Text.Length; ++i)
				{
					if (textBox7.Text[i] != charMemory)
					{
						equalityFlag = false;
					}
				}
				if (equalityFlag)
				{
					label9.Text = Convert.ToString("Цифры числа равны");
				}
				else
				{
					label9.Text = Convert.ToString("Цифры числа НЕ равны");
				}
			}
			else
			{
				label9.Text = Convert.ToString("Разрядность НЕ равна трем");
			}
		}
	}
}
