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
using System.IO.Compression;
using System.Security.Cryptography;

namespace lab5
{
    public partial class From_Notatnik : Form
    {
        public From_Notatnik()
        {
            InitializeComponent();
        }

        private void button_Browse_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog2 = new OpenFileDialog
            {
                InitialDirectory = "c:\\" ,  
                Title = "Przeglądaj pliki tekstowe" ,  
  
                CheckFileExists = true ,  
                CheckPathExists = true ,  
  
                DefaultExt = "txt" ,  
                Filter = "pliki txt (* .txt) | * .txt" ,  
                FilterIndex = 2,  
                RestoreDirectory = true ,  
                ShowReadOnly = true
            };
            if (openFileDialog2.ShowDialog() == DialogResult.OK)
            {
                textBox_Access_Path.Text = openFileDialog2.FileName;
            }
        }

        private void toolStripMenu_Display_Click(object sender, EventArgs e)
        {
            string path = textBox_Access_Path.Text;
            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read);
            StreamReader sr = new StreamReader(fs);
            richTextBox_Edit_Field.Text = sr.ReadToEnd();
            sr.Close();
            fs.Close();
            /*
            while (!sr.EndOfStream)
            {
                richTextBox_Edit_Field.Text = sr.ReadLine();
            }
            */
            /*
            using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
            {
                byte[] data = new byte[fs.Length];
                UTF8Encoding temp = new UTF8Encoding(true);
                while (fs.Read(data, 0, (int)fs.Length) > 0)
                {
                    richTextBox_Edit_Field.Text = temp.GetString(data);
                }
                fs.Close();
            }
            */
        }

        private void toolStripMenu_Save_Click(object sender, EventArgs e)
        {
            string path = textBox_Access_Path.Text;
            FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write);
            StreamWriter sr = new StreamWriter(fs);
            sr.WriteLine(richTextBox_Edit_Field.Text);
            sr.Close();
            fs.Close();
            if (checkBox_Compress.Checked)
            {
                using (FileStream inputStream = new FileStream(path, FileMode.OpenOrCreate, FileAccess.ReadWrite))
                {
                    using (FileStream outputStream = new FileStream(path + ".gzip", FileMode.OpenOrCreate, FileAccess.ReadWrite))
                    {
                        using (GZipStream gzip = new GZipStream(outputStream, CompressionMode.Compress))
                        {
                            inputStream.CopyTo(gzip);
                        }
                    }
                }
            } 
            if(checkBox_Cipher.Checked)
            {
                byte[] key = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 }; 
                Aes cipher = Aes.Create();
                cipher.Key = key;
                using (FileStream outfs = new FileStream(path + ".enc", FileMode.Create))
                {
                    byte[] iv = cipher.IV;
                    outfs.Write(iv, 0, iv.Length);
                    using (CryptoStream cryptStream = new CryptoStream(outfs, cipher.CreateEncryptor(), CryptoStreamMode.Write))
                    {
                        using (StreamWriter streamwr = new StreamWriter(cryptStream))
                        {
                            streamwr.WriteLine(richTextBox_Edit_Field);
                        }
                    }
                }
            }

            /*
            string path = textBox_Access_Path.Text;
            using (FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write))
            { 
                byte[] data = new UTF8Encoding(true).GetBytes(richTextBox_Edit_Field.Text);
                fs.Write(data, 0, data.Length);
            }
            */
        }

        private void toolStripMenu_Clear_Click(object sender, EventArgs e)
        {
            richTextBox_Edit_Field.Text = null;
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

    }
}
