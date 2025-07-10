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
using System.Text.RegularExpressions;

namespace CSharp_lab9
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
			richTextBox1.ReadOnly = true;
			richTextBox2.ReadOnly = true;
			dict = new ArrayList(100);
		}

		private Form2 dictWindow;
		public ArrayList dict;

		public void dictAdd(string toAdd)
		{
			switch (dict.Count)
			{
				case 0:
					dict.Add(toAdd);
					break;
				default:
					var iter = dict.GetEnumerator();
					int i = 0;
					bool insertDone = false;
					while (!insertDone)
					{
						if (iter.MoveNext())
						{
							if (string.Compare(toAdd, (string)iter.Current) <= 0)
							{
								dict.Insert(i, toAdd);
								insertDone = true;
							}
							++i;
						}
						else
						{
							break;
						}
					}
					if (!insertDone)
					{
						dict.Insert(i, toAdd);
					}
					break;
			}
		}

		private void button1_Click(object sender, EventArgs e)
		{
			try
			{
				richTextBox1.Text = File.ReadAllText(@"IN.txt");
				if (richTextBox1.Text.Length == 0)
				{
					throw new Exception();
				}
			}
			catch (Exception)
			{
				label1.Text = "[!] Ошибка чтения IN.txt";
				return;
			}
			label1.Text = "___";
			
			richTextBox1.Text = Regex.Replace(richTextBox1.Text, @"[^\w\s]", "");
			richTextBox1.Text = richTextBox1.Text.ToLower();
			var words = new List<string>(richTextBox1.Text.Split(' '));
			while (words.Contains(""))
			{
				words.Remove("");
			}
			label3.Text = string.Format("Количество символов: {0}\nКоличество слов: {1}", richTextBox1.Text.Length, words.Count);
			foreach (var word in words)
			{
				if (!dict.Contains(word))
				{
					dictAdd(word);
				}
			}
			// dict.Sort();
		}

		private void RichTextBoxAppendTextColor(ref RichTextBox box, string text, Color color)
		{
			
			box.SelectionStart = box.TextLength;
			box.SelectionLength = 0;
			box.SelectionColor = color;
			var fontMemorized = box.SelectionFont;
			box.SelectionFont = new Font(box.Font, FontStyle.Bold);
			box.AppendText(text);
			box.SelectionFont = fontMemorized;
			box.SelectionColor = box.ForeColor;
		}

		private void button2_Click(object sender, EventArgs e)
		{
			if (richTextBox1.Text.Length != 0 & textBox1.Text.Length != 0)
			{
				var coloredIndexes = new List<int>();
				var coloredRanges = new List<object[]>();
				int prevPos = -1;
				int currPos = 0;
				while ((currPos = richTextBox1.Text.IndexOf(textBox1.Text, prevPos + 1)) != -1)
				{
					coloredIndexes.Add(currPos);
					prevPos = currPos;
				}
				label2.Text = "___";
				label4.Text = string.Format("Размер подстроки: {0}\nКоличество вхождений: {1}", textBox1.Text.Length, coloredIndexes.Count);
				if (coloredIndexes.Count == 0)
				{
					label2.Text = "[!] Не найдено";
					return;
				}
				else if (coloredIndexes.Count == 1)
				{
					coloredRanges.Add(new object[] { new int[] { 0, coloredIndexes[0] - 1 }, false });
					coloredRanges.Add(new object[] { new int[] { coloredIndexes[0], coloredIndexes[0] + textBox1.Text.Length - 1 }, true });
					coloredRanges.Add(new object[] { new int[] { coloredIndexes[0] + textBox1.Text.Length, richTextBox1.Text.Length - 1 }, false });
				}
				else if (coloredIndexes.Count == 2)
				{
					coloredRanges.Add(new object[] { new int[] { 0, coloredIndexes[0] - 1 }, false });
					coloredRanges.Add(new object[] { new int[] { coloredIndexes[0], coloredIndexes[0] + textBox1.Text.Length - 1 }, true });
					coloredRanges.Add(new object[] { new int[] { coloredIndexes[0] + textBox1.Text.Length, coloredIndexes[1] - 1 }, false });
					coloredRanges.Add(new object[] { new int[] { coloredIndexes[1], coloredIndexes[1] + textBox1.Text.Length - 1 }, true });
					coloredRanges.Add(new object[] { new int[] { coloredIndexes[1] + textBox1.Text.Length, richTextBox1.Text.Length - 1 }, false });
				}
				else
				{
					for (int i = 0; i < coloredIndexes.Count - 1; ++i)
					{
						if (i == 0)
						{
							coloredRanges.Add(new object[] { new int[] { 0, coloredIndexes[i] - 1 }, false });
							coloredRanges.Add(new object[] { new int[] { coloredIndexes[i], coloredIndexes[i] + textBox1.Text.Length - 1 }, true });
							coloredRanges.Add(new object[] { new int[] { coloredIndexes[i] + textBox1.Text.Length, coloredIndexes[i + 1] - 1 }, false });
						}
						else
						{
							coloredRanges.Add(new object[] { new int[] { coloredIndexes[i], coloredIndexes[i] + textBox1.Text.Length - 1 }, true });
							coloredRanges.Add(new object[] { new int[] { coloredIndexes[i] + textBox1.Text.Length, coloredIndexes[i + 1] - 1 }, false });
							if (i == coloredIndexes.Count - 2)
							{
								coloredRanges.Add(new object[] { new int[] { coloredIndexes[i + 1], coloredIndexes[i + 1] + textBox1.Text.Length - 1 }, true });
								coloredRanges.Add(new object[] { new int[] { coloredIndexes[i + 1] + textBox1.Text.Length, richTextBox1.Text.Length - 1 }, false });
							}
						}
					}
				}
				richTextBox2.Text = "";
				int temp1, temp2;
				foreach (var item in coloredRanges)
				{
					temp1 = ((int[])item[0])[0];
					temp2 = ((int[])item[0])[1] - temp1 + 1;
					if ((bool)item[1])
					{
						RichTextBoxAppendTextColor(ref richTextBox2, richTextBox1.Text.Substring(temp1, temp2), Color.Red);
					}
					else
					{
						richTextBox2.AppendText(richTextBox1.Text.Substring(temp1, temp2));
					}
				}
			}
			else
			{
				label2.Text = "[!] Текст или подстрока отсутствуют";
			}
		}

		private void button3_Click(object sender, EventArgs e)
		{
			MessageBox.Show(this, "Автор текста - файл IN.txt", "Автор текста - файл IN.txt", MessageBoxButtons.OK);
		}

		private void button4_Click(object sender, EventArgs e)
		{
			dictWindow = new Form2(this);
			dictWindow.Show();
		}
	}
}
