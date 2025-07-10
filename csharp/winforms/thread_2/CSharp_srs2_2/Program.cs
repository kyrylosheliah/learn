using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;

namespace CSharp_srs2_2
{
	class Program
	{
		static void Main(string[] args)
		{
			string input;
			try
			{
				input = File.ReadAllText("in.txt");
			}
			catch (Exception)
			{
				Console.WriteLine("Ошибка чтения");
				Console.ReadKey();
				return;
			}

			if (!(input.Length == 0))
			{
				int maxWorkThreads;
				int maxIOThreads;
				ThreadPool.GetMaxThreads(out maxWorkThreads, out maxIOThreads);
				Console.WriteLine("Макс. рабочих потоков {0}\nМакс. потоков ввод-вывод {1}", maxWorkThreads, maxIOThreads);
				Console.WriteLine("Считан текст, " + input.Length + " символов");
				Console.WriteLine("Запуск задачи ...");
				int step;
				if (input.Length >= 2000)
				{
					step = (int)(input.Length / 10) - 1;
				}
				else if (input.Length >= 500)
				{
					step = (int)(input.Length / 5) - 1;
				}
				else
				{
					step = input.Length - 1;
				}
				var threads = new List<Thread>(256);
				List<char> chars = new List<char>(64);
				chars.AddRange(Enumerable.Range(0, 32).Select((x, i) => (char)('а' + i)));
				chars.AddRange(Enumerable.Range(0, 32).Select((x, i) => (char)('А' + i)));
				chars.AddRange(Enumerable.Range(0, 26).Select((x, i) => (char)('a' + i)));
				chars.AddRange(Enumerable.Range(0, 26).Select((x, i) => (char)('A' + i)));
				var outputCharInts = new List<CharInt>(116);
				for (int i = 0; i < chars.Count; ++i)
				{
					//threads.Add(new Thread(new ParameterizedThreadStart(CountChar)));
					ThreadPool.QueueUserWorkItem(CountChar, new string_string_ListCharInt(input, outputCharInts, chars[i]));
				}
				/*
				for (int i = 0; i < chars.Count; ++i)
				{
					threads[i].Start(new string_string_ListCharInt(input, outputCharInts, chars[i]));
				}
				foreach (Thread thread in threads)
				{
					thread.Join();
				}
				Console.WriteLine("Получены данные задачи:");
				foreach (CharInt item in outputCharInts.OrderBy(item => item.interger))
				{
					Console.WriteLine("Символ '" + item.character + "', число вхождений [" + item.interger + "]");
				}
				*/
				Console.WriteLine("Конец Program::Main");
			}
			else
			{
				Console.WriteLine("Результат чтения - пусто");
			}
			Console.ReadKey();
		}

		static object locker = new object();
		static void CountChar(Object parameters)
		{
			Console.WriteLine("Start " + Thread.CurrentThread.ManagedThreadId);
			var input = (string_string_ListCharInt)parameters;
			int counter = 0;
			for (int i = 0; i < input.data.Length; ++i)
			{
				if (input.data[i] == input.sought)
				{
					++counter;
				}
			}
			if (counter > 0)
			{
				/*
				lock (locker)
				{
					input.toreturn.Add(new CharInt(input.sought, counter));
				}
				*/
				Console.WriteLine("End " + Thread.CurrentThread.ManagedThreadId + " | '" + input.sought + "' - " + counter);
			}
		}
	}

	public class CharInt
	{
		public char character;
		public int interger;
		public CharInt(char ch, int num)
		{
			character = ch;
			interger = num;
		}
	}

	public class string_string_ListCharInt
	{
		public string data { get; }
		public List<CharInt> toreturn;
		public char sought;

		public string_string_ListCharInt(string inputData, List<CharInt> inputReturn, char inputSought)
		{
			data = inputData;
			toreturn = inputReturn;
			sought = inputSought;
		}
	}
}
