using System;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace CSharp_lab8
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
            checkedListBox1.Items.Add(Color.White);
            checkedListBox1.Items.Add(Color.Black);
            checkedListBox1.Items.Add(Color.Red);
            checkedListBox1.Items.Add(Color.Green);
            checkedListBox1.Items.Add(Color.Blue);
            checkedListBox1.Items.Add(Color.Orange);
            checkedListBox1.Items.Add(Color.Yellow);
            checkedListBox1.Items.Add(Color.Cyan);
            checkedListBox1.Items.Add(Color.Purple);

            graphics1 = pictureBox1.CreateGraphics();
            graphics2 = pictureBox2.CreateGraphics();
            graphics1.Clear(Color.White);
            pen = new Pen(Color.Black, 3f);
        }

        private Graphics graphics1;
        private Graphics graphics2;
        private Pen pen;

        private IList<IList<string>> Permute(string[] dataFrom)
        {
            var list = new List<IList<string>>();
            return DoPermute(dataFrom, 0, dataFrom.Length - 1, list);
        }

        private IList<IList<string>> DoPermute(string[] dataFrom, int start, int end, IList<IList<string>> list)
        {
            if (start == end)
            {
                list.Add(new List<string>(dataFrom));
            }
            else
            {
                for (int i = start; i <= end; ++i)
                {
                    Swap(ref dataFrom[start], ref dataFrom[i]);
                    DoPermute(dataFrom, start + 1, end, list);
                    Swap(ref dataFrom[start], ref dataFrom[i]);
                }
            }
            return list;
        }

        private void Swap(ref string a, ref string b)
        {
            string temp = a;
            a = b;
            b = temp;
        }

        private void button1_Click(object sender, EventArgs e)
		{
            try
            {
                richTextBox2.Text = "";
                richTextBox1.Text = File.ReadAllText(@"IN.txt");
                if (richTextBox1.Text.Length == 0) { throw new Exception(); }
                string[] dataFrom = richTextBox1.Text.Split(' ');
                foreach (var perm in Permute(dataFrom))
                {
                    richTextBox2.Text += string.Join(" ", perm) + "\n";
                }
                label1.Text = "IN.txt прочитан";
                File.WriteAllText(@"OUT.txt", richTextBox2.Text);
                label2.Text = "OUT.txt записан";
            }
            catch
            {
                label1.Text = "[!] ОШИБКА чтения";
                label2.Text = "[!] OUT.txt не записан";
            }
        }


        IEnumerable<List<T>> GetVariations<T>(List<T> offers, int length)
        {
            var startIndices = new int[length];
            var variationElements = new HashSet<T>();

            while (startIndices[0] < offers.Count)
            {
                var variation = new List<T>(length);
                var valid = true;
                for (int i = 0; i < length; ++i)
                {
                    var element = offers[startIndices[i]];
                    if (variationElements.Contains(element))
                    {
                        valid = false;
                        break;
                    }
                    variation.Add(element);
                    variationElements.Add(element);
                }
                if (valid)
                {
                    yield return variation;
                }

                startIndices[length - 1]++;
                for (int i = length - 1; i > 0; --i)
                {
                    if (startIndices[i] >= offers.Count)
                    {
                        startIndices[i] = 0;
                        startIndices[i - 1]++;
                    }
                    else
                    {
                        break;
                    }
                }
                variationElements.Clear();
            }
        }

        private void button2_Click(object sender, EventArgs e)
		{
            try
            {
                richTextBox4.Text = "";
                richTextBox3.Text = File.ReadAllText(@"IN.txt");
                if (richTextBox3.Text.Length == 0) { throw new Exception(); }
                int count = (int)uint.Parse(textBox1.Text);
                if (count < 1) { throw new Exception(); }
                var dataFrom = new List<string>(richTextBox3.Text.Split(' '));
                IEnumerable<List<string>> permsLength = GetVariations<string>(dataFrom, count);
                foreach (var perm in permsLength)
                {
                    richTextBox4.Text += string.Join(" ", perm) + "\n";
                }
                label3.Text = "IN.txt прочитан";
                File.WriteAllText(@"OUT.txt", richTextBox4.Text);
                label4.Text = "OUT.txt записан";
                
            }
            catch
            {
                label3.Text = "[!] ОШИБКА чтения";
                label4.Text = "[!] OUT.txt не записан";
            }
        }

		private void button4_Click(object sender, EventArgs e)
		{
            CheckedListBox userPaletteListChoise = null;
            if (radioButton1.Checked)
            { userPaletteListChoise = checkedListBox1; }
            else if (radioButton2.Checked)
            { userPaletteListChoise = checkedListBox2; }
            if (userPaletteListChoise != null)
            {
                if (userPaletteListChoise.Items.Count != 0)
                {
                    int a, r, g, b;
                    a = r = g = b = 0;
                    int i = 0;
                    foreach (int checkedIndex in userPaletteListChoise.CheckedIndices)
                    {
                        a += ((Color)userPaletteListChoise.Items[checkedIndex]).A;
                        r += ((Color)userPaletteListChoise.Items[checkedIndex]).R;
                        g += ((Color)userPaletteListChoise.Items[checkedIndex]).G;
                        b += ((Color)userPaletteListChoise.Items[checkedIndex]).B;
                        ++i;
                    }
                    a /= i; r /= i; g /= i; b /= i;
                    pen.Color = Color.FromArgb(a, r, g, b);
                }
            }
            graphics2.Clear(pen.Color);
            label8.Text = pen.Color.ToString();
        }

		private void button3_Click(object sender, EventArgs e)
		{
            int colorA, colorR, colorG, colorB;
            try
			{
                colorA = (int)uint.Parse(textBox2.Text);
                colorR = (int)uint.Parse(textBox3.Text);
                colorG = (int)uint.Parse(textBox4.Text);
                colorB = (int)uint.Parse(textBox5.Text);
                if (colorA > 255 | colorR > 255 | colorG > 255 | colorB > 255)
                { throw new Exception(); }
                checkedListBox2.Items.Add(Color.FromArgb(colorA, colorR, colorG, colorB));
                label9.Text = "___";
            }
			catch
			{
                label9.Text = "[!] Ошибка значений";
			}
		}

		private void button5_Click(object sender, EventArgs e)
		{
            graphics1.Clear(Color.White);
        }

		private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
		{
            graphics1.DrawEllipse(pen, e.Location.X, e.Location.Y, 3, 3);
        }
	}
}
