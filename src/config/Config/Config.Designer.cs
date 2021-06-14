namespace config
{
    partial class config
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(config));
            this.ResolutionLabel = new System.Windows.Forms.Label();
            this.ResolutionList = new System.Windows.Forms.ComboBox();
            this.FrequencyLabel = new System.Windows.Forms.Label();
            this.FrequencyList = new System.Windows.Forms.ComboBox();
            this.GammaLabel = new System.Windows.Forms.Label();
            this.GammaList = new System.Windows.Forms.ComboBox();
            this.DisplayBox = new System.Windows.Forms.GroupBox();
            this.ExitButton = new System.Windows.Forms.Button();
            this.WindowModeButton = new System.Windows.Forms.RadioButton();
            this.FullScreenModeButton = new System.Windows.Forms.RadioButton();
            this.WindowLabel = new System.Windows.Forms.Label();
            this.WindowBox = new System.Windows.Forms.GroupBox();
            this.InternalIMEButton = new System.Windows.Forms.RadioButton();
            this.ExternalIMEButton = new System.Windows.Forms.RadioButton();
            this.Label1 = new System.Windows.Forms.Label();
            this.IMEBox = new System.Windows.Forms.GroupBox();
            this.BGMLabel = new System.Windows.Forms.Label();
            this.SFXButton = new System.Windows.Forms.Label();
            this.BGMBar = new System.Windows.Forms.TrackBar();
            this.SFXBar = new System.Windows.Forms.TrackBar();
            this.SoundBox = new System.Windows.Forms.GroupBox();
            this.CursorButton = new System.Windows.Forms.CheckBox();
            this.FogLabel = new System.Windows.Forms.Label();
            this.TNLLabel = new System.Windows.Forms.Label();
            this.ShadowLabel = new System.Windows.Forms.Label();
            this.FogList = new System.Windows.Forms.ComboBox();
            this.TNLList = new System.Windows.Forms.ComboBox();
            this.ShadowList = new System.Windows.Forms.ComboBox();
            this.GFXBox = new System.Windows.Forms.GroupBox();
            this.SaveButton = new System.Windows.Forms.Button();
            this.DisplayBox.SuspendLayout();
            this.WindowBox.SuspendLayout();
            this.IMEBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BGMBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SFXBar)).BeginInit();
            this.SoundBox.SuspendLayout();
            this.GFXBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // ResolutionLabel
            // 
            this.ResolutionLabel.AutoSize = true;
            this.ResolutionLabel.Location = new System.Drawing.Point(19, 20);
            this.ResolutionLabel.Name = "ResolutionLabel";
            this.ResolutionLabel.Size = new System.Drawing.Size(57, 13);
            this.ResolutionLabel.TabIndex = 0;
            this.ResolutionLabel.Text = "Résolution";
            // 
            // ResolutionList
            // 
            this.ResolutionList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ResolutionList.FormattingEnabled = true;
            this.ResolutionList.Location = new System.Drawing.Point(82, 17);
            this.ResolutionList.Name = "ResolutionList";
            this.ResolutionList.Size = new System.Drawing.Size(125, 21);
            this.ResolutionList.TabIndex = 1;
            // 
            // FrequencyLabel
            // 
            this.FrequencyLabel.AutoSize = true;
            this.FrequencyLabel.Location = new System.Drawing.Point(18, 45);
            this.FrequencyLabel.Name = "FrequencyLabel";
            this.FrequencyLabel.Size = new System.Drawing.Size(58, 13);
            this.FrequencyLabel.TabIndex = 2;
            this.FrequencyLabel.Text = "Fréquence";
            // 
            // FrequencyList
            // 
            this.FrequencyList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FrequencyList.FormattingEnabled = true;
            this.FrequencyList.Location = new System.Drawing.Point(82, 42);
            this.FrequencyList.Name = "FrequencyList";
            this.FrequencyList.Size = new System.Drawing.Size(125, 21);
            this.FrequencyList.TabIndex = 3;
            // 
            // GammaLabel
            // 
            this.GammaLabel.AutoSize = true;
            this.GammaLabel.Location = new System.Drawing.Point(33, 67);
            this.GammaLabel.Name = "GammaLabel";
            this.GammaLabel.Size = new System.Drawing.Size(43, 13);
            this.GammaLabel.TabIndex = 4;
            this.GammaLabel.Text = "Gamma";
            // 
            // GammaList
            // 
            this.GammaList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.GammaList.FormattingEnabled = true;
            this.GammaList.Location = new System.Drawing.Point(82, 67);
            this.GammaList.Name = "GammaList";
            this.GammaList.Size = new System.Drawing.Size(125, 21);
            this.GammaList.TabIndex = 5;
            // 
            // DisplayBox
            // 
            this.DisplayBox.Controls.Add(this.GammaList);
            this.DisplayBox.Controls.Add(this.GammaLabel);
            this.DisplayBox.Controls.Add(this.FrequencyList);
            this.DisplayBox.Controls.Add(this.FrequencyLabel);
            this.DisplayBox.Controls.Add(this.ResolutionList);
            this.DisplayBox.Controls.Add(this.ResolutionLabel);
            this.DisplayBox.Location = new System.Drawing.Point(12, 12);
            this.DisplayBox.Name = "DisplayBox";
            this.DisplayBox.Size = new System.Drawing.Size(213, 100);
            this.DisplayBox.TabIndex = 10;
            this.DisplayBox.TabStop = false;
            this.DisplayBox.Text = "Affichage";
            // 
            // ExitButton
            // 
            this.ExitButton.Location = new System.Drawing.Point(231, 251);
            this.ExitButton.Name = "ExitButton";
            this.ExitButton.Size = new System.Drawing.Size(208, 39);
            this.ExitButton.TabIndex = 19;
            this.ExitButton.Text = "Annuler";
            this.ExitButton.UseVisualStyleBackColor = true;
            this.ExitButton.Click += new System.EventHandler(this.ExitButton_Click);
            // 
            // WindowModeButton
            // 
            this.WindowModeButton.AutoSize = true;
            this.WindowModeButton.Location = new System.Drawing.Point(7, 19);
            this.WindowModeButton.Name = "WindowModeButton";
            this.WindowModeButton.Size = new System.Drawing.Size(61, 17);
            this.WindowModeButton.TabIndex = 0;
            this.WindowModeButton.Text = "Fenêtre";
            this.WindowModeButton.UseVisualStyleBackColor = true;
            // 
            // FullScreenModeButton
            // 
            this.FullScreenModeButton.AutoSize = true;
            this.FullScreenModeButton.Location = new System.Drawing.Point(116, 20);
            this.FullScreenModeButton.Name = "FullScreenModeButton";
            this.FullScreenModeButton.Size = new System.Drawing.Size(78, 17);
            this.FullScreenModeButton.TabIndex = 1;
            this.FullScreenModeButton.Text = "Plein écran";
            this.FullScreenModeButton.UseVisualStyleBackColor = true;
            // 
            // WindowLabel
            // 
            this.WindowLabel.AutoSize = true;
            this.WindowLabel.Location = new System.Drawing.Point(83, 22);
            this.WindowLabel.Name = "WindowLabel";
            this.WindowLabel.Size = new System.Drawing.Size(10, 13);
            this.WindowLabel.TabIndex = 2;
            this.WindowLabel.Text = "-";
            // 
            // WindowBox
            // 
            this.WindowBox.Controls.Add(this.WindowLabel);
            this.WindowBox.Controls.Add(this.FullScreenModeButton);
            this.WindowBox.Controls.Add(this.WindowModeButton);
            this.WindowBox.Location = new System.Drawing.Point(232, 13);
            this.WindowBox.Name = "WindowBox";
            this.WindowBox.Size = new System.Drawing.Size(200, 49);
            this.WindowBox.TabIndex = 12;
            this.WindowBox.TabStop = false;
            this.WindowBox.Text = "Mode fenêtré";
            // 
            // InternalIMEButton
            // 
            this.InternalIMEButton.AutoSize = true;
            this.InternalIMEButton.Location = new System.Drawing.Point(7, 19);
            this.InternalIMEButton.Name = "InternalIMEButton";
            this.InternalIMEButton.Size = new System.Drawing.Size(58, 17);
            this.InternalIMEButton.TabIndex = 0;
            this.InternalIMEButton.TabStop = true;
            this.InternalIMEButton.Text = "Interne";
            this.InternalIMEButton.UseVisualStyleBackColor = true;
            // 
            // ExternalIMEButton
            // 
            this.ExternalIMEButton.AutoSize = true;
            this.ExternalIMEButton.Location = new System.Drawing.Point(116, 20);
            this.ExternalIMEButton.Name = "ExternalIMEButton";
            this.ExternalIMEButton.Size = new System.Drawing.Size(61, 17);
            this.ExternalIMEButton.TabIndex = 1;
            this.ExternalIMEButton.TabStop = true;
            this.ExternalIMEButton.Text = "Externe";
            this.ExternalIMEButton.UseVisualStyleBackColor = true;
            // 
            // Label1
            // 
            this.Label1.AutoSize = true;
            this.Label1.Location = new System.Drawing.Point(83, 22);
            this.Label1.Name = "Label1";
            this.Label1.Size = new System.Drawing.Size(10, 13);
            this.Label1.TabIndex = 2;
            this.Label1.Text = "-";
            // 
            // IMEBox
            // 
            this.IMEBox.Controls.Add(this.Label1);
            this.IMEBox.Controls.Add(this.ExternalIMEButton);
            this.IMEBox.Controls.Add(this.InternalIMEButton);
            this.IMEBox.Location = new System.Drawing.Point(232, 63);
            this.IMEBox.Name = "IMEBox";
            this.IMEBox.Size = new System.Drawing.Size(200, 49);
            this.IMEBox.TabIndex = 13;
            this.IMEBox.TabStop = false;
            this.IMEBox.Text = "Mode IME";
            // 
            // BGMLabel
            // 
            this.BGMLabel.AutoSize = true;
            this.BGMLabel.Location = new System.Drawing.Point(6, 19);
            this.BGMLabel.Name = "BGMLabel";
            this.BGMLabel.Size = new System.Drawing.Size(52, 13);
            this.BGMLabel.TabIndex = 0;
            this.BGMLabel.Text = "Musiques";
            // 
            // SFXButton
            // 
            this.SFXButton.AutoSize = true;
            this.SFXButton.Location = new System.Drawing.Point(6, 55);
            this.SFXButton.Name = "SFXButton";
            this.SFXButton.Size = new System.Drawing.Size(51, 13);
            this.SFXButton.TabIndex = 1;
            this.SFXButton.Text = "Bruitages";
            // 
            // BGMBar
            // 
            this.BGMBar.Location = new System.Drawing.Point(64, 19);
            this.BGMBar.Maximum = 50;
            this.BGMBar.Name = "BGMBar";
            this.BGMBar.Size = new System.Drawing.Size(141, 45);
            this.BGMBar.TabIndex = 2;
            // 
            // SFXBar
            // 
            this.SFXBar.Location = new System.Drawing.Point(64, 55);
            this.SFXBar.Maximum = 50;
            this.SFXBar.Name = "SFXBar";
            this.SFXBar.Size = new System.Drawing.Size(141, 45);
            this.SFXBar.TabIndex = 3;
            // 
            // SoundBox
            // 
            this.SoundBox.Controls.Add(this.SFXBar);
            this.SoundBox.Controls.Add(this.BGMBar);
            this.SoundBox.Controls.Add(this.SFXButton);
            this.SoundBox.Controls.Add(this.BGMLabel);
            this.SoundBox.Location = new System.Drawing.Point(13, 119);
            this.SoundBox.Name = "SoundBox";
            this.SoundBox.Size = new System.Drawing.Size(212, 94);
            this.SoundBox.TabIndex = 14;
            this.SoundBox.TabStop = false;
            this.SoundBox.Text = "Sons";
            // 
            // CursorButton
            // 
            this.CursorButton.AutoSize = true;
            this.CursorButton.Location = new System.Drawing.Point(12, 219);
            this.CursorButton.Name = "CursorButton";
            this.CursorButton.Size = new System.Drawing.Size(173, 17);
            this.CursorButton.TabIndex = 15;
            this.CursorButton.Text = "Ne pas utiliser le curseur du jeu";
            this.CursorButton.UseVisualStyleBackColor = true;
            // 
            // FogLabel
            // 
            this.FogLabel.AutoSize = true;
            this.FogLabel.Location = new System.Drawing.Point(12, 19);
            this.FogLabel.Name = "FogLabel";
            this.FogLabel.Size = new System.Drawing.Size(50, 13);
            this.FogLabel.TabIndex = 0;
            this.FogLabel.Text = "Brouillard";
            // 
            // TNLLabel
            // 
            this.TNLLabel.AutoSize = true;
            this.TNLLabel.Location = new System.Drawing.Point(18, 46);
            this.TNLLabel.Name = "TNLLabel";
            this.TNLLabel.Size = new System.Drawing.Size(44, 13);
            this.TNLLabel.TabIndex = 1;
            this.TNLLabel.Text = "Support";
            // 
            // ShadowLabel
            // 
            this.ShadowLabel.AutoSize = true;
            this.ShadowLabel.Location = new System.Drawing.Point(19, 73);
            this.ShadowLabel.Name = "ShadowLabel";
            this.ShadowLabel.Size = new System.Drawing.Size(43, 13);
            this.ShadowLabel.TabIndex = 2;
            this.ShadowLabel.Text = "Ombres";
            // 
            // FogList
            // 
            this.FogList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FogList.FormattingEnabled = true;
            this.FogList.Location = new System.Drawing.Point(73, 16);
            this.FogList.Name = "FogList";
            this.FogList.Size = new System.Drawing.Size(121, 21);
            this.FogList.TabIndex = 3;
            // 
            // TNLList
            // 
            this.TNLList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.TNLList.FormattingEnabled = true;
            this.TNLList.Location = new System.Drawing.Point(73, 43);
            this.TNLList.Name = "TNLList";
            this.TNLList.Size = new System.Drawing.Size(121, 21);
            this.TNLList.TabIndex = 4;
            // 
            // ShadowList
            // 
            this.ShadowList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ShadowList.FormattingEnabled = true;
            this.ShadowList.Location = new System.Drawing.Point(73, 70);
            this.ShadowList.Name = "ShadowList";
            this.ShadowList.Size = new System.Drawing.Size(121, 21);
            this.ShadowList.TabIndex = 5;
            // 
            // GFXBox
            // 
            this.GFXBox.Controls.Add(this.ShadowList);
            this.GFXBox.Controls.Add(this.TNLList);
            this.GFXBox.Controls.Add(this.FogList);
            this.GFXBox.Controls.Add(this.ShadowLabel);
            this.GFXBox.Controls.Add(this.TNLLabel);
            this.GFXBox.Controls.Add(this.FogLabel);
            this.GFXBox.Location = new System.Drawing.Point(232, 119);
            this.GFXBox.Name = "GFXBox";
            this.GFXBox.Size = new System.Drawing.Size(200, 100);
            this.GFXBox.TabIndex = 16;
            this.GFXBox.TabStop = false;
            this.GFXBox.Text = "Graphismes";
            // 
            // SaveButton
            // 
            this.SaveButton.Location = new System.Drawing.Point(12, 251);
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(213, 39);
            this.SaveButton.TabIndex = 18;
            this.SaveButton.Text = "Sauvegarder";
            this.SaveButton.UseVisualStyleBackColor = true;
            this.SaveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // config
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(451, 302);
            this.Controls.Add(this.ExitButton);
            this.Controls.Add(this.SaveButton);
            this.Controls.Add(this.GFXBox);
            this.Controls.Add(this.CursorButton);
            this.Controls.Add(this.SoundBox);
            this.Controls.Add(this.IMEBox);
            this.Controls.Add(this.WindowBox);
            this.Controls.Add(this.DisplayBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "config";
            this.Text = "Metin2 Project Config Files #ASIKOO";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.DisplayBox.ResumeLayout(false);
            this.DisplayBox.PerformLayout();
            this.WindowBox.ResumeLayout(false);
            this.WindowBox.PerformLayout();
            this.IMEBox.ResumeLayout(false);
            this.IMEBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BGMBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SFXBar)).EndInit();
            this.SoundBox.ResumeLayout(false);
            this.SoundBox.PerformLayout();
            this.GFXBox.ResumeLayout(false);
            this.GFXBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        internal System.Windows.Forms.Label ResolutionLabel;
        internal System.Windows.Forms.ComboBox ResolutionList;
        internal System.Windows.Forms.Label FrequencyLabel;
        internal System.Windows.Forms.ComboBox FrequencyList;
        internal System.Windows.Forms.Label GammaLabel;
        internal System.Windows.Forms.ComboBox GammaList;
        internal System.Windows.Forms.GroupBox DisplayBox;
        internal System.Windows.Forms.Button ExitButton;
        internal System.Windows.Forms.RadioButton WindowModeButton;
        internal System.Windows.Forms.RadioButton FullScreenModeButton;
        internal System.Windows.Forms.Label WindowLabel;
        internal System.Windows.Forms.GroupBox WindowBox;
        internal System.Windows.Forms.RadioButton InternalIMEButton;
        internal System.Windows.Forms.RadioButton ExternalIMEButton;
        internal System.Windows.Forms.Label Label1;
        internal System.Windows.Forms.GroupBox IMEBox;
        internal System.Windows.Forms.Label BGMLabel;
        internal System.Windows.Forms.Label SFXButton;
        internal System.Windows.Forms.TrackBar BGMBar;
        internal System.Windows.Forms.TrackBar SFXBar;
        internal System.Windows.Forms.GroupBox SoundBox;
        internal System.Windows.Forms.CheckBox CursorButton;
        internal System.Windows.Forms.Label FogLabel;
        internal System.Windows.Forms.Label TNLLabel;
        internal System.Windows.Forms.Label ShadowLabel;
        internal System.Windows.Forms.ComboBox FogList;
        internal System.Windows.Forms.ComboBox TNLList;
        internal System.Windows.Forms.ComboBox ShadowList;
        internal System.Windows.Forms.GroupBox GFXBox;
        internal System.Windows.Forms.Button SaveButton;
    }
}

