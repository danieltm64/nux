// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using Nux.Extensions;

namespace HelloCs
{
    class MainWindow : Nux.Window
    {
        public MainWindow()
            : base("¯\\_(ツ)_/¯", 800, 600, Nux.WindowMode.Standard)
        {
            RootLayout.Kind = Nux.LayoutKind.Fixed;

            _groupBox = RootLayout.AddWidget<Nux.GroupBox>();
            _groupBox.ContentLayout.Kind = Nux.LayoutKind.Fixed;
            _groupBox.Title = "Vector Graphics";

            _graphicsBox = _groupBox.AddWidget<Nux.GraphicsBox>();

            _rectangle = Nux.VectorPath.BuildRectangle(10, 10, 80, 80, 10);
            List<Nux.GradientStop> gradientStops1 = new List<Nux.GradientStop>();
            gradientStops1.Add(new Nux.GradientStop(0, new Nux.GVector4D(1, 0, 0, 1)));
            gradientStops1.Add(new Nux.GradientStop(0.5f, new Nux.GVector4D(0, 1, 0, 1)));
            gradientStops1.Add(new Nux.GradientStop(1, new Nux.GVector4D(0, 0, 1, 1)));
            _linearGradientPaint = Nux.Paint.BuildLinearGradient(new Nux.GVector2D(0, 0), new Nux.GVector2D(100, 100), gradientStops1);

            _circle = Nux.VectorPath.BuildCircle(50, 50, 25);
            List<Nux.GradientStop> gradientStops2 = new List<Nux.GradientStop>();
            gradientStops2.Add(new Nux.GradientStop(0, new Nux.GVector4D(1, 1, 1, 1)));
            gradientStops2.Add(new Nux.GradientStop(1, new Nux.GVector4D(1, 1, 1, 0)));
            _radialGradientPaint = Nux.Paint.BuildRadialGradient(new Nux.GVector2D(50, 50), 25, gradientStops2);

            _graphicsBox.OnRender = RenderGraphicsBox;

            _helloLabel = RootLayout.AddWidget<Nux.Label>();
            _helloLabel.Text = "Made in C#";

            _enableToggleButton = RootLayout.AddWidget<Nux.CheckBox>();
            _enableToggleButton.Text = "Enable Toggle button";
            _enableToggleButton.OnToggle = EnableToggleButtonClicked;

            _toggleButton = RootLayout.AddWidget<Nux.PushButton>();
            _toggleButton.Text = "Toggle";
            _toggleButton.OnTrigger = ToggleButtonClicked;

            _group1 = new Nux.CheckGroup();

            _option1 = RootLayout.AddWidget<Nux.RadioButton>(_group1);
            _option1.Text = "Yellow Background";
            _option1.OnToggle = Option1Toggled;

            _option2 = RootLayout.AddWidget<Nux.RadioButton>(_group1);
            _option2.Text = "Orange Background";
            _option2.OnToggle = Option2Toggled;

            _clearColor = new Nux.GVector4D(1, 1, 0, 1);

            _enableToggleButton.Checked = true;
            _option1.Checked = true;

            int x = 10;
            int y = 0;
            int maxWidth = 0;
            int maxHeight = 0;

            _groupBox.X = x;
            _groupBox.Y = (y += 10);
            _groupBox.Width = 100 + _groupBox.HorizontalOverhead;
            _groupBox.Height = 100 + _groupBox.VerticalOverhead;
            y += _groupBox.Height;
            maxWidth = Math.Max(maxWidth, _groupBox.X + _groupBox.Width);
            maxHeight = Math.Max(maxHeight, _groupBox.Y + _groupBox.Height);

            _graphicsBox.X = 0;
            _graphicsBox.Y = 0;
            _graphicsBox.Width = 100;
            _graphicsBox.Height = 100;

            _helloLabel.X = x;
            _helloLabel.Y = (y += 10);
            y += _helloLabel.Height;
            maxWidth = Math.Max(maxWidth, _helloLabel.X + _helloLabel.Width);
            maxHeight = Math.Max(maxHeight, _helloLabel.Y + _helloLabel.Height);

            x = _groupBox.X + _groupBox.Width + 10;
            y = 0;

            _enableToggleButton.X = x;
            _enableToggleButton.Y = (y += 10);
            y += _enableToggleButton.Height;
            maxWidth = Math.Max(maxWidth, _enableToggleButton.X + _enableToggleButton.Width);
            maxHeight = Math.Max(maxHeight, _enableToggleButton.Y + _enableToggleButton.Height);

            _toggleButton.X = x;
            _toggleButton.Y = (y += 10);
            y += _toggleButton.Height;
            maxWidth = Math.Max(maxWidth, _toggleButton.X + _toggleButton.Width);
            maxHeight = Math.Max(maxHeight, _toggleButton.Y + _toggleButton.Height);

            _option1.X = x;
            _option1.Y = (y += 10);
            y += _option1.Height;
            maxWidth = Math.Max(maxWidth, _option1.X + _option1.Width);
            maxHeight = Math.Max(maxHeight, _option1.Y + _option1.Height);

            _option2.X = x;
            _option2.Y = (y += 10);
            y += _option2.Height;
            maxWidth = Math.Max(maxWidth, _option2.X + _option2.Width);
            maxHeight = Math.Max(maxHeight, _option2.Y + _option2.Height);

            Width = maxWidth + 10;
            Height = maxHeight + 10;

            Center();
            RootLayout.Show();
        }

        public override void HandleCloseEvent(Nux.CloseEvent e)
        {
            string confirm = "Confirm";
            if (Title != confirm)
            {
                Title = confirm;
                e.ShouldClose = false;
            }
        }

        private void RenderGraphicsBox()
        {
            _graphicsBox.Clear(_clearColor.X, _clearColor.Y, _clearColor.Z, _clearColor.W);
            _graphicsBox.FillPath(_rectangle, _linearGradientPaint);
            _graphicsBox.FillPath(_circle, _radialGradientPaint);
        }

        private void EnableToggleButtonClicked()
        {
            _toggleButton.Enabled = _enableToggleButton.Checked;
        }

        private void ToggleButtonClicked()
        {
            if (_option1.Checked)
            {
                _option2.Checked = true;
            }
            else
            {
                _option1.Checked = true;
            }
        }

        private void Option1Toggled()
        {
            _clearColor.X = 1;
            _clearColor.Y = 1;
            _clearColor.Z = 0;
            _clearColor.W = 1;
        }

        private void Option2Toggled()
        {
            _clearColor.X = 1;
            _clearColor.Y = 0.65f;
            _clearColor.Z = 0;
            _clearColor.W = 1;
        }

        private Nux.GroupBox _groupBox;
        private Nux.GraphicsBox _graphicsBox;
        private Nux.VectorPath _rectangle;
        private Nux.Paint _linearGradientPaint;
        private Nux.VectorPath _circle;
        private Nux.Paint _radialGradientPaint;
        private Nux.Label _helloLabel;

        private Nux.CheckBox _enableToggleButton;
        private Nux.PushButton _toggleButton;

        private Nux.CheckGroup _group1;
        private Nux.RadioButton _option1;
        private Nux.RadioButton _option2;
        private Nux.GVector4D _clearColor;
    }

    class Program
    {
        static int Main(string[] args)
        {
            Nux.Application application = new Nux.Application(args);
            Console.WriteLine(Nux.Application.Encoding);

            MainWindow window = new MainWindow();
            window.Show();

            return application.Run();
        }
    }
}
