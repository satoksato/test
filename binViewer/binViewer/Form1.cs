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

namespace binViewer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            UpdateTextBox2FromCurrentFile();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            UpdateTextBox2FromCurrentFile();
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            comboBox1.Items.AddRange(new object[] { "char", "short", "int", "float", "double" });
            comboBox1.SelectedIndex = 0;
            textBox1.Text = Directory.GetCurrentDirectory();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(textBox1.Text) && System.IO.Directory.Exists(textBox1.Text))
            {
                openFileDialog1.InitialDirectory = textBox1.Text;
            }
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = openFileDialog1.FileName;
                UpdateTextBox2FromCurrentFile();
            }
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateTextBox2FromCurrentFile();
        }

        private bool IsLittleEndian()
        {
            // radioButton1: LittleEndian, radioButton2: BigEndian
            if (radioButton1.Checked) return true;
            if (radioButton2.Checked) return false;
            return BitConverter.IsLittleEndian;
        }

        private void UpdateTextBox2FromCurrentFile()
        {
            var path = textBox1.Text;
            if (string.IsNullOrEmpty(path) || !System.IO.File.Exists(path))
            {
                return;
            }

            string mode = (comboBox1.SelectedItem as string)?.Trim().ToLowerInvariant() ?? string.Empty;
            var littleEndian = IsLittleEndian();

            try
            {
                switch (mode)
                {
                    case "char":
                        textBox2.Text = ConvertDirectBytesToHex(path);
                        break;

                        case "short":
                        textBox2.Text = ConvertToTypedBinaryHex(path, 2, littleEndian);
                        break;

                    case "int":
                        textBox2.Text = ConvertToTypedBinaryHex(path, 4, littleEndian);
                        break;

                    case "float":
                        textBox2.Text = ConvertToTypedBinaryHex(path, 4, littleEndian);
                        break;

                    case "double":
                        textBox2.Text = ConvertToTypedBinaryHex(path, 8, littleEndian);
                        break;

                    default:
                        textBox2.Text = System.IO.File.ReadAllText(path);
                        break;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("ファイル読み込み中にエラーが発生しました:\n" + ex.Message, "エラー", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private string ConvertToTypedBinaryHex(string path, int size, bool littleEndian)
        {
            var bytes = System.IO.File.ReadAllBytes(path);
            if (bytes.Length < size) return string.Empty;

            var sb = new StringBuilder();
            for (int i = 0; i + size <= bytes.Length; i += size)
            {
                var chunk = new byte[size];
                Array.Copy(bytes, i, chunk, 0, size);

                if (!littleEndian)
                {
                    Array.Reverse(chunk);
                }

                if (sb.Length > 0) sb.Append(" ");
                sb.Append(string.Join(" ", chunk.Select(b => b.ToString("X2"))));
            }

            return sb.ToString();
        }

        private string ConvertDirectBytesToHex(string path)
        {
            var bytes = System.IO.File.ReadAllBytes(path);
            return string.Join(" ", bytes.Select(b => b.ToString("X2")));
        }
    }
}
