using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace CSharp_lab10
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
			comboBox1.Items.AddRange(new object[]{
				"Вырезать",
				"Заменить",
				"Удалить"
			});
			comboBox2.Items.AddRange(new object[]{
				"Подстроку",
				"Остальное"
			});
		}

		private Func<Action<int, int>, int, int, string> delegateFunction;
		private Action<int, int> delegateAction;
		private int delegateFromParam, delegateToParam;

		private List<int[]> markup = new List<int[]>();
		private List<string> strarrtmp = new List<string>();

		private void MarkDownSubstring(int fromIndex, int toIndex)
		{
			markup.Clear();
			markup.Add(new int[] { fromIndex, toIndex - fromIndex + ((fromIndex == toIndex) ? (0) : (1)) });
		}
		private void MarkDownTheRest(int fromIndex, int toIndex)
		{
			markup.Clear();
			markup.Add(new int[] { 0, ((fromIndex == 0) ? (0) : (fromIndex - ((fromIndex == toIndex) ? (0) : (1)))) });
			markup.Add(new int[] { ((toIndex == 0) ? (richTextBox1.Text.Length - 1) : (toIndex + ((fromIndex == toIndex) ? (0) : (1)))), richTextBox1.Text.Length - toIndex - 1 });
		}

		private string CutSelection(Action<int, int> act, int fromIndex, int toIndex)
		{
			act(fromIndex, toIndex);
			strarrtmp.Clear();
			foreach (var range in markup)
			{
				strarrtmp.Add(richTextBox1.Text.Substring(range[0], range[1]));
			}
			for (int i = markup.Count - 1; i >= 0; --i)
			{
				richTextBox1.Text = richTextBox1.Text.Remove(markup[i][0], markup[i][1]);
			}
			listBox1.Items.Add(string.Join(" ", strarrtmp));
			return string.Join(" ", strarrtmp);
		}

		private string ReplaceSelection(Action<int, int> act, int fromIndex, int toIndex)
		{
			if (textBox1.Text.Length == 0)
			{
				return "___";
			}
			act(fromIndex, toIndex);
			strarrtmp.Clear();
			foreach (var range in markup)
			{
				strarrtmp.Add(richTextBox1.Text.Substring(range[0], range[1]));
			}
			for (int i = markup.Count - 1; i >= 0; --i)
			{
				richTextBox1.Text = richTextBox1.Text.Remove(markup[i][0], markup[i][1]);
				richTextBox1.Text = richTextBox1.Text.Insert(markup[i][0], textBox1.Text);
			}
			return string.Join(" ", strarrtmp);
		}

		private string RemoveSelection(Action<int, int> act, int fromIndex, int toIndex)
		{
			act(fromIndex, toIndex);
			strarrtmp.Clear();
			foreach (var range in markup)
			{
				strarrtmp.Add(richTextBox1.Text.Substring(range[0], range[1]));
			}
			for (int i = markup.Count - 1; i >= 0; --i)
			{
				richTextBox1.Text = richTextBox1.Text.Remove(markup[i][0], markup[i][1]);
			}
			return string.Join(" ", strarrtmp);
		}

		private void button1_Click(object sender, EventArgs e)
		{
			if (delegateFunction == null || delegateAction == null || richTextBox1.Text.Length == 0)
			{
				label1.Text = "[!] Ошибка входных параметров";
			}
			else
			{
				label1.Text = string.Format("\"{0}\"", delegateFunction(delegateAction, delegateFromParam, delegateToParam));
			}
		}

		private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch ((string)comboBox1.SelectedItem)
			{
				case "Вырезать":
					delegateFunction = CutSelection;
					break;
				case "Заменить":
					delegateFunction = ReplaceSelection;
					break;
				case "Удалить":
					delegateFunction = RemoveSelection;
					break;
			}
		}

		private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch ((string)comboBox2.SelectedItem)
			{
				case "Подстроку":
					delegateAction = MarkDownSubstring;
					break;
				case "Остальное":
					delegateAction = MarkDownTheRest;
					break;
			}
		}

		private void richTextBox1_SelectionChanged(object sender, EventArgs e)
		{
			delegateFromParam = richTextBox1.SelectionStart;
			delegateToParam = delegateFromParam + ((richTextBox1.SelectionLength == 0)?(1):(richTextBox1.SelectionLength)) - 1;
		}

		private void button2_Click(object sender, EventArgs e)
		{
			try
			{
				richTextBox1.Text = File.ReadAllText(@"IN.txt");
				if (richTextBox1.Text.Length == 0)
				{
					throw new Exception();
				}
				label2.Text = "___";
			}
			catch
			{
				label2.Text = "[!] Ошибка чтения IN.txt";
				return;
			}
		}
	}
}
