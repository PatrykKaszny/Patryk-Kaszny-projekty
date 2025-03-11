namespace GrayscaleConv
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.threadsBar = new System.Windows.Forms.TrackBar();
            this.selectedC = new System.Windows.Forms.RadioButton();
            this.selectedAsm = new System.Windows.Forms.RadioButton();
            this.label4 = new System.Windows.Forms.Label();
            this.threadsVal = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lightBar = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.threadsBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lightBar)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.Sienna;
            this.button1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.ForeColor = System.Drawing.Color.White;
            this.button1.Location = new System.Drawing.Point(465, 405);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(112, 40);
            this.button1.TabIndex = 1;
            this.button1.Text = "Wybierz plik";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.label2.Location = new System.Drawing.Point(135, 419);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(200, 29);
            this.label2.TabIndex = 10;
            this.label2.Text = "Wybierz liczbę wątków";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // threadsBar
            // 
            this.threadsBar.Location = new System.Drawing.Point(139, 451);
            this.threadsBar.Maximum = 64;
            this.threadsBar.Minimum = 1;
            this.threadsBar.Name = "threadsBar";
            this.threadsBar.Size = new System.Drawing.Size(181, 56);
            this.threadsBar.TabIndex = 4;
            this.threadsBar.TickFrequency = 5;
            this.threadsBar.Value = 1;
            this.threadsBar.Scroll += new System.EventHandler(this.numThreadsValue);
            // 
            // selectedC
            // 
            this.selectedC.Checked = true;
            this.selectedC.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.selectedC.Location = new System.Drawing.Point(470, 557);
            this.selectedC.Name = "selectedC";
            this.selectedC.Size = new System.Drawing.Size(104, 22);
            this.selectedC.TabIndex = 0;
            this.selectedC.TabStop = true;
            this.selectedC.Text = "C++";
            // 
            // selectedAsm
            // 
            this.selectedAsm.AutoSize = true;
            this.selectedAsm.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.selectedAsm.Location = new System.Drawing.Point(470, 517);
            this.selectedAsm.Name = "selectedAsm";
            this.selectedAsm.Size = new System.Drawing.Size(99, 24);
            this.selectedAsm.TabIndex = 7;
            this.selectedAsm.TabStop = true;
            this.selectedAsm.Text = "Assembler";
            this.selectedAsm.UseVisualStyleBackColor = true;
            this.selectedAsm.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(0, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(100, 23);
            this.label4.TabIndex = 0;
            // 
            // threadsVal
            // 
            this.threadsVal.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold);
            this.threadsVal.Location = new System.Drawing.Point(341, 451);
            this.threadsVal.Name = "threadsVal";
            this.threadsVal.Size = new System.Drawing.Size(30, 20);
            this.threadsVal.TabIndex = 11;
            this.threadsVal.Text = "1";
            this.threadsVal.Click += new System.EventHandler(this.threadsVal_Click);
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.ForestGreen;
            this.button2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.ForeColor = System.Drawing.Color.White;
            this.button2.Location = new System.Drawing.Point(465, 451);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(112, 40);
            this.button2.TabIndex = 12;
            this.button2.Text = "Konwertuj";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(487, 379);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 13;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Click += new System.EventHandler(this.pictureBox1_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox2.Location = new System.Drawing.Point(549, 12);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(487, 379);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox2.TabIndex = 14;
            this.pictureBox2.TabStop = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.label5.Location = new System.Drawing.Point(959, 463);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(0, 20);
            this.label5.TabIndex = 15;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.label1.Location = new System.Drawing.Point(706, 419);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(200, 29);
            this.label1.TabIndex = 17;
            this.label1.Text = "Wybierz próg jasności";
            this.label1.Click += new System.EventHandler(this.label1_Click_1);
            // 
            // lightBar
            // 
            this.lightBar.Location = new System.Drawing.Point(710, 451);
            this.lightBar.Maximum = 255;
            this.lightBar.Name = "lightBar";
            this.lightBar.Size = new System.Drawing.Size(189, 56);
            this.lightBar.TabIndex = 16;
            this.lightBar.TickFrequency = 5;
            this.lightBar.Value = 1;
            this.lightBar.Scroll += new System.EventHandler(this.lightBar_Scroll);
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold);
            this.label3.Location = new System.Drawing.Point(923, 451);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(30, 20);
            this.label3.TabIndex = 18;
            this.label3.Text = "1";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.ClientSize = new System.Drawing.Size(1049, 591);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lightBar);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.selectedAsm);
            this.Controls.Add(this.selectedC);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.threadsBar);
            this.Controls.Add(this.threadsVal);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.label5);
            this.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.Name = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load_1);
            ((System.ComponentModel.ISupportInitialize)(this.threadsBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lightBar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #region Windows Form Designer generated code
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TrackBar threadsBar;
        private System.Windows.Forms.RadioButton selectedC;
        private System.Windows.Forms.RadioButton selectedAsm;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label threadsVal;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Label label5;
        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TrackBar lightBar;
        private System.Windows.Forms.Label label3;
    }
}