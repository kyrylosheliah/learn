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
using Excel = Microsoft.Office.Interop.Excel;

namespace CSharp_lab4
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}
		//StringBuilder
		private void button1_Click(object sender, EventArgs e)
		{
			richTextBox1.Text = "";
			label2.Text = "___";
			try
			{
				richTextBox1.Text = File.ReadAllText(@"IN.txt");
				label2.Text = "Файл загружен";
			}
			catch (FileNotFoundException)
			{
				richTextBox1.Text += "\n[!] ОШИБКА: файл не найден\n";
				label2.Text = "[!] ОШИБКА: файл не найден";
			}
			catch (DirectoryNotFoundException)
			{
				richTextBox1.Text += "[!] ОШИБКА: папка не найдена";
				label2.Text = "[!] ОШИБКА: папка не найдена";
			}
			catch (FileLoadException)
			{
				richTextBox1.Text += "[!] ОШИБКА: не удалось загрузить файл";
				label2.Text = "[!] ОШИБКА: не удалось загрузить файл";
			}
			catch (DriveNotFoundException)
			{
				richTextBox1.Text += "[!] ОШИБКА: диск не найден";
				label2.Text = "[!] ОШИБКА: диск не найден";
			}
			catch (PathTooLongException)
			{
				richTextBox1.Text += "[!] ОШИБКА: слишком длинное имя пути";
				label2.Text = "[!] ОШИБКА: слишком длинное имя пути";
			}
			catch (IOException except)
			{
				richTextBox1.Text += "[!] " + except.ToString();
				label2.Text = "[!] ОШИБКА";
			}
		}

		private List<string> sortedLines = null;

		private void button2_Click(object sender, EventArgs e)
		{
			if (textBox1.Text.Length == 1)
			{
				if (richTextBox1.Text.Length != 0)
				{
					char sought = textBox1.Text[0];
					List<string> lines = new List<string>(richTextBox1.Text.Split('\n'));
					for (int i = lines.Count - 1; i >= 0; --i)
					{
						if (lines[i].IndexOf(sought) == -1)
						{
							lines.RemoveAt(i);
						}
					}
					sortedLines = lines.OrderBy(str => str.Length).ToList();
					richTextBox1.Text += "\n\nВыполнены отсеивание по содержанию символа и сортировка по размеру строки:\n";
					if (sortedLines.Count == 0)
					{
						richTextBox1.Text += "<ПУСТО>\n";
					}
					else
					{
						foreach (var line in sortedLines)
						{
							richTextBox1.Text += line + "\n";
						}
					}
					
					label4.Text = "Задание выполнено";
				}
				else
				{
					label4.Text = "Считаные данные отсутствуют";
				}
			}
			else
			{
				label4.Text = "[!] Введите ОДИН символ";
			}
		}

		private async void button3_Click(object sender, EventArgs e)
		{
			label5.Text = "___";
			try
			{
				using (StreamWriter sw = new StreamWriter(@"OUT.txt", true, Encoding.Default))
				{
					await sw.WriteLineAsync(string.Format("\n>>> Начало записи {0}\n{1}\n>>> Конец записи {0}", DateTime.Today.ToString(), richTextBox1.Text));
				}
				label5.Text = "OUT.txt записан";
			}
			catch (FileNotFoundException)
			{
				label5.Text = "[!] ОШИБКА: файл не найден";
			}
			catch (DirectoryNotFoundException)
			{
				label5.Text = "[!] ОШИБКА: папка не найдена";
			}
			catch (FileLoadException)
			{
				label5.Text = "[!] ОШИБКА: не удалось загрузить файл";
			}
			catch (DriveNotFoundException)
			{
				label5.Text = "[!] ОШИБКА: диск не найден";
			}
			catch (PathTooLongException)
			{
				label5.Text = "[!] ОШИБКА: слишком длинное имя пути";
			}
			catch (IOException except)
			{
				label5.Text = "[!] ОШИБКА: " + except.ToString();
			}
		}

		private void button4_Click(object sender, EventArgs e)
		{
			if (sortedLines != null)
			{
				Excel.Application excelApp = new Excel.Application();
				Excel.Workbook excelWorkbook = null;
				try
				{
					excelWorkbook = excelApp.Workbooks.Open(@"OUT.xlsx");
				}
				catch
				{
					excelWorkbook = excelApp.Workbooks.Add();
				}
				Excel.Worksheet excelWorksheet = excelWorkbook.Sheets[1];
				for (int i = 0; i < sortedLines.Count; ++i)
				{
					excelWorksheet.Cells[i + 1, "A"].Value = sortedLines[i];
				}
				excelWorkbook.SaveAs(Directory.GetCurrentDirectory() + "\\OUT.xlsx");
				excelWorkbook.Close(false); // закрыть и не сохранять
				excelApp.Quit();
				label6.Text = "Книга сохранена";
			}
			else
			{
				label6.Text = "[!] ОШИБКА: массив не иниализирован заданием";
			}
			
		}
	}
}
