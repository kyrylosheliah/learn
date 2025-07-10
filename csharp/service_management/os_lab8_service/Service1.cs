using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Threading;

namespace os_lab8_service
{
	public partial class oslab8service : ServiceBase
	{
		Logger logger;
		public oslab8service()
		{
			InitializeComponent();
		}

		protected override void OnStart(string[] args)
		{
			logger = new Logger();
			Thread loggerThread = new Thread(new ThreadStart(logger.Start));
			loggerThread.Start();
		}

		protected override void OnStop()
		{
			logger.Stop();
			Thread.Sleep(1000);
		}

		protected override void OnPause()
		{
			logger.Pause();
		}

		protected override void OnContinue()
		{
			logger.Continue();
		}
	}

	class Logger
	{
		private FileSystemWatcher watcher;
		private object obj = new object();
		private bool enabled = true;
		public Logger()
		{
			watcher = new FileSystemWatcher("D:\\Temp");
			watcher.Deleted += Watcher_Deleted;
			watcher.Created += Watcher_Created;
			watcher.Changed += Watcher_Changed;
			watcher.Renamed += Watcher_Renamed;
		}

		public void Start()
		{
			watcher.EnableRaisingEvents = true;
			while (enabled)
			{
				Thread.Sleep(1000);
			}
		}
		public void Stop()
		{
			watcher.EnableRaisingEvents = false;
			enabled = false;
		}

		public void Pause()
		{
			watcher.EnableRaisingEvents = false;
		}

		public void Continue()
		{
			watcher.EnableRaisingEvents = true;
		}

		private void Watcher_Renamed(object sender, RenamedEventArgs e)
		{
			string fileEvent = "переименован в " + e.FullPath;
			string filePath = e.OldFullPath;
			RecordEntry(fileEvent, filePath);
		}

		private void Watcher_Changed(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "изменен";
			string filePath = e.FullPath;
			RecordEntry(fileEvent, filePath);
		}

		private void Watcher_Created(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "создан";
			string filePath = e.FullPath;
			RecordEntry(fileEvent, filePath);
		}
		private void Watcher_Deleted(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "удален";
			string filePath = e.FullPath;
			RecordEntry(fileEvent, filePath);
		}

		private void RecordEntry(string fileEvent, string filePath)
		{
			lock (obj)
			{
				using (StreamWriter writer = new StreamWriter("D:\\oslab8_log.txt", true))
				{
					writer.WriteLine(String.Format("{0} файл {1} был {2}", DateTime.Now.ToString("dd/MM/yyyy hh:mm:ss"), filePath, fileEvent));
					writer.Flush();
				}
			}
		}
	}
}
