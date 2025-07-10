using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net.Http;
using System.Security.Policy;
using System.Net;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Reflection.Metadata;
using static System.Net.WebRequestMethods;
using System.Xml;
using System.Security.Authentication;
using System.Xml.Linq;

namespace rwd_lab8
{

    public partial class Form1 : Form
    {
        private static readonly CookieContainer _cookieContainer;
        private static readonly HttpClient _client;
        private static int _counter;
        private static readonly List<List<string>> _urls;

        static Form1()
        {
            _cookieContainer = new CookieContainer();
            _client = new HttpClient(new HttpClientHandler()
            {
                CookieContainer = _cookieContainer,
                //ServerCertificateCustomValidationCallback = (sender, cert, chain, sslPolicyErrors) => { return true; },
                //SslProtocols = SslProtocols.Tls12 | SslProtocols.Tls11 | SslProtocols.Tls
            });
            _client.BaseAddress = new Uri("https://localhost:44390/");
            _counter = 0;
            _urls = new List<List<string>>
            {
                new List<string> {"lab8_1_BaseOperations.asmx/Binary", "string"},
                new List<string> {"lab8_1_BaseOperations.asmx/Octal", "string"},
                new List<string> {"lab8_1_BaseOperations.asmx/Hexadecimal", "string"},
                new List<string> {"lab8_2_GetDate.asmx/CurrentDayOfMonth", "string"},
                new List<string> {"lab8_2_GetDate.asmx/CurrentDayOfWeek", "string"},
                new List<string> {"lab8_2_GetDate.asmx/CurrentDayOfYear", "string"},
                new List<string> {"lab8_3_Math.asmx/Sum", "double"},
                new List<string> {"lab8_3_Math.asmx/Sub", "double"},
                new List<string> {"lab8_3_Math.asmx/Mul", "double"},
                new List<string> {"lab8_3_Math.asmx/Div", "double"},
                new List<string> {"lab8_3_Math.asmx/Pow", "double"}
            };
        }

        public Form1()
        {
            InitializeComponent();
            textBox4.Text = _client.BaseAddress.ToString();
            comboBox1.Items.AddRange(_urls.Select(x => x[0]).ToArray());
            comboBox1.SelectedIndex = _counter;
        }

        async private void button1_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            FormUrlEncodedContent content;
            HttpResponseMessage response;
            string responseString;

            Dictionary<string, string> values;
            if (_counter < 3)
            {
                values = new Dictionary<string, string>
                {
                    { "x", textBox1.Text}
                };
            }
            else if (_counter < 6)
            {
                values = new Dictionary<string, string>{};
            }
            else
            {
                values = new Dictionary<string, string>
                {
                    { "a", textBox1.Text},
                    { "b", textBox2.Text},
                };
            }
            content = new FormUrlEncodedContent(values);

            richTextBox1.Text += await content.ReadAsStringAsync();
            try
            {
                response = await _client.PostAsync(_urls[_counter][0], content);
                response.EnsureSuccessStatusCode();
                responseString = await response.Content.ReadAsStringAsync();

                richTextBox1.Text += "\n\n" + responseString;

                var doc = XDocument.Parse(responseString);
                label5.Text = doc.Root.Value;
            }
            catch (Exception)
            {
                label5.Text = "_";
                richTextBox1.Text += "\n\nBAD REQUEST";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            _counter = (_counter + 1 >= _urls.Count) ? (0) : (_counter + 1);
            if (textBox4.Text != _client.BaseAddress.ToString())
            {
                _client.BaseAddress = new Uri(textBox4.Text);
            }
            comboBox1.SelectedIndex = _counter;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            _counter = _urls.FindIndex(x => x[0].Equals(comboBox1.SelectedItem.ToString()));
            comboBox1.SelectedIndex = _counter;
        }

        /*private string FormSubmission(string url, string postData)
        {
            WebRequest request = WebRequest.Create(url);

            byte[] send = Encoding.Default.GetBytes(postData);
            request.Method = "POST";
            request.ContentType = "application/x-www-form-urlencoded";
            request.ContentLength = send.Length;

            Stream sout = request.GetRequestStream();
            sout.Write(send, 0, send.Length);
            sout.Flush();
            sout.Close();

            WebResponse res = request.GetResponse();
            StreamReader sr = new StreamReader(res.GetResponseStream());
            string returnValue = sr.ReadToEnd();

            return returnValue;
        }*/
    }
}
