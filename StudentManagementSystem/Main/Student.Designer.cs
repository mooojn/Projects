namespace DBProject
{
    partial class Student
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.panel1 = new System.Windows.Forms.Panel();
            this.addStudentPanel = new System.Windows.Forms.Panel();
            this.status = new System.Windows.Forms.CheckBox();
            this.udBtn = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.stdContactBox = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.deleteBtn = new System.Windows.Forms.Button();
            this.updateBtn = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.stdRegNoBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.stdEmailBox = new System.Windows.Forms.TextBox();
            this.stdLastNameBox = new System.Windows.Forms.TextBox();
            this.stdFirstNameBox = new System.Windows.Forms.TextBox();
            this.addBtn = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.panel1.SuspendLayout();
            this.addStudentPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.panel1.Controls.Add(this.addStudentPanel);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1417, 855);
            this.panel1.TabIndex = 0;
            // 
            // addStudentPanel
            // 
            this.addStudentPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.addStudentPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(91)))), ((int)(((byte)(100)))));
            this.addStudentPanel.Controls.Add(this.dataGridView1);
            this.addStudentPanel.Controls.Add(this.status);
            this.addStudentPanel.Controls.Add(this.udBtn);
            this.addStudentPanel.Controls.Add(this.label3);
            this.addStudentPanel.Controls.Add(this.stdContactBox);
            this.addStudentPanel.Controls.Add(this.button3);
            this.addStudentPanel.Controls.Add(this.deleteBtn);
            this.addStudentPanel.Controls.Add(this.updateBtn);
            this.addStudentPanel.Controls.Add(this.label5);
            this.addStudentPanel.Controls.Add(this.stdRegNoBox);
            this.addStudentPanel.Controls.Add(this.label4);
            this.addStudentPanel.Controls.Add(this.label2);
            this.addStudentPanel.Controls.Add(this.label1);
            this.addStudentPanel.Controls.Add(this.stdEmailBox);
            this.addStudentPanel.Controls.Add(this.stdLastNameBox);
            this.addStudentPanel.Controls.Add(this.stdFirstNameBox);
            this.addStudentPanel.Controls.Add(this.addBtn);
            this.addStudentPanel.Location = new System.Drawing.Point(0, 0);
            this.addStudentPanel.Name = "addStudentPanel";
            this.addStudentPanel.Size = new System.Drawing.Size(1417, 855);
            this.addStudentPanel.TabIndex = 32;
            this.addStudentPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.addStudentPanel_Paint);
            // 
            // status
            // 
            this.status.AutoSize = true;
            this.status.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(231)))), ((int)(((byte)(246)))), ((int)(((byte)(242)))));
            this.status.Location = new System.Drawing.Point(535, 170);
            this.status.Name = "status";
            this.status.Size = new System.Drawing.Size(103, 29);
            this.status.TabIndex = 28;
            this.status.Text = "Active";
            this.status.UseVisualStyleBackColor = true;
            this.status.CheckedChanged += new System.EventHandler(this.status_CheckedChanged);
            // 
            // udBtn
            // 
            this.udBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(165)))), ((int)(((byte)(201)))), ((int)(((byte)(202)))));
            this.udBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.udBtn.Location = new System.Drawing.Point(478, 253);
            this.udBtn.Name = "udBtn";
            this.udBtn.Size = new System.Drawing.Size(168, 65);
            this.udBtn.TabIndex = 26;
            this.udBtn.Text = "Hide UD Buttons";
            this.udBtn.UseVisualStyleBackColor = false;
            this.udBtn.Click += new System.EventHandler(this.hideUdBtn_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(231)))), ((int)(((byte)(246)))), ((int)(((byte)(242)))));
            this.label3.Location = new System.Drawing.Point(530, 106);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(86, 25);
            this.label3.TabIndex = 25;
            this.label3.Text = "Contact";
            // 
            // stdContactBox
            // 
            this.stdContactBox.Location = new System.Drawing.Point(645, 100);
            this.stdContactBox.Name = "stdContactBox";
            this.stdContactBox.Size = new System.Drawing.Size(241, 31);
            this.stdContactBox.TabIndex = 24;
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(165)))), ((int)(((byte)(201)))), ((int)(((byte)(202)))));
            this.button3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.button3.Location = new System.Drawing.Point(478, 364);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(168, 65);
            this.button3.TabIndex = 23;
            this.button3.Text = "Mark Attendance";
            this.button3.UseVisualStyleBackColor = false;
            this.button3.Click += new System.EventHandler(this.Mark_Attendance);
            // 
            // deleteBtn
            // 
            this.deleteBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(165)))), ((int)(((byte)(201)))), ((int)(((byte)(202)))));
            this.deleteBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.deleteBtn.Location = new System.Drawing.Point(696, 253);
            this.deleteBtn.Name = "deleteBtn";
            this.deleteBtn.Size = new System.Drawing.Size(168, 65);
            this.deleteBtn.TabIndex = 22;
            this.deleteBtn.Text = "Delete Record";
            this.deleteBtn.UseVisualStyleBackColor = false;
            this.deleteBtn.Click += new System.EventHandler(this.Delete_Student);
            // 
            // updateBtn
            // 
            this.updateBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(165)))), ((int)(((byte)(201)))), ((int)(((byte)(202)))));
            this.updateBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.updateBtn.Location = new System.Drawing.Point(268, 253);
            this.updateBtn.Name = "updateBtn";
            this.updateBtn.Size = new System.Drawing.Size(168, 65);
            this.updateBtn.TabIndex = 21;
            this.updateBtn.Text = "Update Record";
            this.updateBtn.UseVisualStyleBackColor = false;
            this.updateBtn.Click += new System.EventHandler(this.Update_Student);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(231)))), ((int)(((byte)(246)))), ((int)(((byte)(242)))));
            this.label5.Location = new System.Drawing.Point(87, 174);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(78, 25);
            this.label5.TabIndex = 20;
            this.label5.Text = "RegNo";
            // 
            // stdRegNoBox
            // 
            this.stdRegNoBox.Location = new System.Drawing.Point(192, 168);
            this.stdRegNoBox.Name = "stdRegNoBox";
            this.stdRegNoBox.Size = new System.Drawing.Size(241, 31);
            this.stdRegNoBox.TabIndex = 19;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(231)))), ((int)(((byte)(246)))), ((int)(((byte)(242)))));
            this.label4.Location = new System.Drawing.Point(540, 37);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 25);
            this.label4.TabIndex = 18;
            this.label4.Text = "Email";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(231)))), ((int)(((byte)(246)))), ((int)(((byte)(242)))));
            this.label2.Location = new System.Drawing.Point(36, 106);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(115, 25);
            this.label2.TabIndex = 16;
            this.label2.Text = "Last Name";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(231)))), ((int)(((byte)(246)))), ((int)(((byte)(242)))));
            this.label1.Location = new System.Drawing.Point(35, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(116, 25);
            this.label1.TabIndex = 15;
            this.label1.Text = "First Name";
            // 
            // stdEmailBox
            // 
            this.stdEmailBox.Location = new System.Drawing.Point(645, 37);
            this.stdEmailBox.Name = "stdEmailBox";
            this.stdEmailBox.Size = new System.Drawing.Size(241, 31);
            this.stdEmailBox.TabIndex = 14;
            // 
            // stdLastNameBox
            // 
            this.stdLastNameBox.Location = new System.Drawing.Point(192, 100);
            this.stdLastNameBox.Name = "stdLastNameBox";
            this.stdLastNameBox.Size = new System.Drawing.Size(241, 31);
            this.stdLastNameBox.TabIndex = 12;
            // 
            // stdFirstNameBox
            // 
            this.stdFirstNameBox.Location = new System.Drawing.Point(192, 31);
            this.stdFirstNameBox.Name = "stdFirstNameBox";
            this.stdFirstNameBox.Size = new System.Drawing.Size(241, 31);
            this.stdFirstNameBox.TabIndex = 11;
            // 
            // addBtn
            // 
            this.addBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(165)))), ((int)(((byte)(201)))), ((int)(((byte)(202)))));
            this.addBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.addBtn.Location = new System.Drawing.Point(478, 253);
            this.addBtn.Name = "addBtn";
            this.addBtn.Size = new System.Drawing.Size(168, 65);
            this.addBtn.TabIndex = 10;
            this.addBtn.Text = "Add Record";
            this.addBtn.UseVisualStyleBackColor = false;
            this.addBtn.Click += new System.EventHandler(this.Add_Student);
            // 
            // dataGridView1
            // 
            this.dataGridView1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView1.BackgroundColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(51)))), ((int)(((byte)(51)))));
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(-231, 544);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 82;
            this.dataGridView1.RowTemplate.Height = 33;
            this.dataGridView1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView1.Size = new System.Drawing.Size(1648, 326);
            this.dataGridView1.TabIndex = 29;
            this.dataGridView1.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.Data_Table_Click);
            // 
            // Student
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1417, 855);
            this.Controls.Add(this.panel1);
            this.MinimumSize = new System.Drawing.Size(820, 520);
            this.Name = "Student";
            this.Load += new System.EventHandler(this.Students_Load);
            this.panel1.ResumeLayout(false);
            this.addStudentPanel.ResumeLayout(false);
            this.addStudentPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel addStudentPanel;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button deleteBtn;
        private System.Windows.Forms.Button updateBtn;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox stdRegNoBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox stdEmailBox;
        private System.Windows.Forms.TextBox stdLastNameBox;
        private System.Windows.Forms.TextBox stdFirstNameBox;
        private System.Windows.Forms.Button addBtn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox stdContactBox;
        private System.Windows.Forms.Button udBtn;
        private System.Windows.Forms.CheckBox status;
        private System.Windows.Forms.DataGridView dataGridView1;
    }
}