using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.ServiceProcess;

namespace os_lab8_manager
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{
            dataGridView1.Rows.Clear(); 
            
            foreach (ServiceController service in ServiceController.GetServices())
            {
                dataGridView1.Rows.Add(
                    service.ServiceName,
                    service.ServiceType.ToString(),
                    service.Status.ToString(),
                    service.CanPauseAndContinue,
                    service.CanShutdown,
                    service.CanStop);
            }
        }

        private void SelectedRowIndexesExecMethod(string method)
        {
            label1.Text = "";
            if (dataGridView1.SelectedRows.Count > 0)
            {
                var indexes = new List<int>(dataGridView1.SelectedRows.Count);
                foreach (DataGridViewRow row in dataGridView1.SelectedRows)
				{
                    ServiceController service = new ServiceController((string)dataGridView1.Rows[row.Index].Cells[0].Value);
					switch (method)
					{
                        case "Start":
                            if (service.Status == ServiceControllerStatus.Stopped)
                            {
                                service.Start();
                            }
                            else if (service.Status == ServiceControllerStatus.Paused && service.CanPauseAndContinue)
                            {
                                service.Continue();
                            }
                            else
                            {
                                label1.Text = "[!] Нельзя запустить сервис " + service.ServiceName;
                            }
                            break;
                        case "Stop":
                            if ((service.Status == ServiceControllerStatus.Running || service.Status == ServiceControllerStatus.Paused) && service.CanStop)
                            {
                                service.Stop();
                            }
                            else
                            {
                                label1.Text = "[!] Нельзя остановить сервис " + service.ServiceName;
                            }
                            break;
                        case "Pause":
                            if (service.Status == ServiceControllerStatus.Running && service.CanPauseAndContinue)
                            {
                                service.Pause();
                            }
                            else
                            {
                                label1.Text = "[!] Нельзя приостановить сервис " + service.ServiceName;
                            }
                            break;
                        case "Restart":
                            if (service.Status == ServiceControllerStatus.Running && service.CanShutdown)
                            {
                                service.Stop();
                                service.Start();
                            }
                            else
                            {
                                label1.Text = "[!] Нельзя перезапустить сервис " + service.ServiceName;
                            }
                            break;
					}
				}
            }
        }

		private void button2_Click(object sender, EventArgs e)
		{
            SelectedRowIndexesExecMethod("Start");
        }

		private void button3_Click(object sender, EventArgs e)
		{
            SelectedRowIndexesExecMethod("Stop");
        }

		private void button4_Click(object sender, EventArgs e)
		{
            SelectedRowIndexesExecMethod("Pause");
        }

		private void button5_Click(object sender, EventArgs e)
		{
            SelectedRowIndexesExecMethod("Restart");
        }
	}
}
