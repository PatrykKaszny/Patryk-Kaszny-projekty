using Grayscale;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Collections.Specialized;

namespace GrayscaleConv
{
    public partial class Form1 : Form
    {
        [DllImport(@"C:\Users\Asus\OneDrive - Politechnika Śląska\Pulpit\Solaryzacja\x64\Debug\ImageProcessingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ApplySolarization(IntPtr pixelData, int width, int height, int stride, int numThreads, byte threshold);

        [DllImport(@"C:\Users\Asus\OneDrive - Politechnika Śląska\Pulpit\Solaryzacja\x64\Debug\JAAsm.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern void ApplySolarizationAsm(IntPtr imageData, int dataSize, int numThreads, byte threshold);



        private Bitmap source;

        private int numThreads = 1;
        private int numLight = 1;
        private string filePath = string.Empty;


        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog fileDialog = new OpenFileDialog())
            {
                fileDialog.Filter = "Image files|*.jpg;*.jpeg;*.png;*.bmp";
                if (fileDialog.ShowDialog() == DialogResult.OK)
                {
                    filePath = fileDialog.FileName;
                    source = new Bitmap(filePath);
                    pictureBox1.Image = source;
                }
            }
        }

        private async void button2_Click(object sender, EventArgs e)
        {
            if (selectedAsm.Checked)
            {
                if (source != null)
                {
                    int width = source.Width;
                    int height = source.Height;

                    // Tworzymy kopię obrazu
                    Bitmap tmp = new Bitmap(source);
                    BitmapData bitmapData = tmp.LockBits(
                        new Rectangle(0, 0, width, height),
                        ImageLockMode.ReadWrite,
                        PixelFormat.Format24bppRgb);

                    IntPtr ptr = bitmapData.Scan0;  // Wskaźnik do danych obrazu
                    int stride = bitmapData.Stride; // Odstęp między wierszami obrazu (rozmiar w bajtach)

                    Stopwatch sw = Stopwatch.StartNew();

                    int numThreads = threadsBar.Value; // Liczba wątków wybrana przez użytkownika
                    byte threshold = (byte)numLight;    // Ustalony próg solaryzacji

                    // Debugowanie - sprawdź wartość threshold
                    Console.WriteLine($"Próg jasności (threshold): {threshold}");

                    // Przekazanie danych obrazu do funkcji assemblera
                    int dataSize = stride * height; // To jest poprawne, ponieważ stride to już pełny rozmiar wiersza obrazu (z uwzględnieniem paddingu)
                    ApplySolarizationAsm(ptr, dataSize, numThreads, threshold); // Przekazanie danych do funkcji assemblera

                    sw.Stop();

                    // Odblokowanie obrazka po przetworzeniu
                    tmp.UnlockBits(bitmapData);

                    // Wyświetlenie przetworzonego obrazu
                    pictureBox2.Image = new Bitmap(tmp);

                    // Wyświetlenie czasu przetwarzania
                    label5.Text = $"Time: {sw.Elapsed.TotalMilliseconds} ms";
                }
                else
                {
                    MessageBox.Show("Nie wybrano pliku", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            else if (selectedC.Checked)
            {
                if (source != null)
                {
                    int width = source.Width;
                    int height = source.Height;

                    Bitmap tmp = new Bitmap(source);
                    BitmapData bitmapData = tmp.LockBits(
                        new Rectangle(0, 0, width, height),
                        ImageLockMode.ReadWrite,
                        PixelFormat.Format32bppArgb);

                    IntPtr ptr = bitmapData.Scan0;
                    int stride = bitmapData.Stride;

                    int threadCount = threadsBar.Value; // Liczba wątków z suwaka
                    byte threshold = (byte)numLight;    // Ustalony próg solaryzacji

                    Stopwatch sw = Stopwatch.StartNew();

                    // Wywołanie funkcji solaryzacji z DLL
                    ApplySolarization(ptr, width, height, stride, threadCount, threshold);

                    sw.Stop();

                    tmp.UnlockBits(bitmapData);
                    pictureBox2.Image = new Bitmap(tmp);
                    label5.Text = $"Czas solaryzacji: {sw.Elapsed.TotalMilliseconds} ms";
                }
                else
                {
                    MessageBox.Show("Nie wybrano pliku", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private void numThreadsValue(object sender, EventArgs e)
        {
            numThreads = threadsBar.Value;
            threadsVal.Text = threadsBar.Value.ToString();
        }

        private void lightBar_Scroll(object sender, EventArgs e)
        {
            numLight = lightBar.Value;
            label3.Text = lightBar.Value.ToString();
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void threadsVal_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }
    }
}
