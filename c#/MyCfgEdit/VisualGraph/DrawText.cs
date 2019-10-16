using System;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing;

namespace VisualGraph
{
    public class DrawText:DrawObject
    {
        private string curText = "text";
        public DrawText(Point point, VisualGraph drawArea)
        {
            ObjName = drawArea.CreateObjName();
            ShapeRect = new Rectangle(point.X, point.Y, Width, Height);
            ObjectType = Global.DrawType.DrawText;
            GenerateID(Global.DrawType.DrawText);
        }
        public void SetAction(string name, object val)
        {
            if (name.Equals(textName))
            {
                curText = val.ToString();
            }else if(name.Equals(xName))
            {
                X = Convert.ToInt32(val);
            }
        }
        
        public string CurText
        {
            get { return curText; }
            set { curText = value; }
        }

        private bool _Show = false;
        public bool ShowEdge
        { get { return _Show; }
            set { _Show = value; }
        }

        private StringFormat _stringFormat = null;
        public StringFormat StringFormat
        {
            get { return _stringFormat; }
            set { _stringFormat = value; }
        }
        public override void Draw(Graphics g, VisualGraph drawArea)
        {
            SolidBrush drawBrush = new SolidBrush(Color.Black);
            Pen fontPen = new Pen(Color, PenWidth);
            if(_stringFormat == null)
            {
                _stringFormat = new StringFormat();
                _stringFormat.Alignment = StringAlignment.Center;
                _stringFormat.LineAlignment = StringAlignment.Center;
            }
            Font drawFont = new Font("Arial", 12);
            g.DrawString(CurText, drawFont, drawBrush, ShapeRect, _stringFormat);
            if(_Show)
            {
                g.DrawRectangle(fontPen, DrawRectangle.GetNormalizedRectangle(ShapeRect));
            }
            drawFont.Dispose();
            drawBrush.Dispose();
            fontPen.Dispose();
        }
        public override int HandleCount
        {
            get { return 4; }
        }

        public override Point GetHandle(int handleNumber)
        {
            int x, y;
            x = ShapeRect.X;
            y = ShapeRect.Y;

            switch (handleNumber)
            {
                case 1:
                    x = ShapeRect.X;
                    y = ShapeRect.Y;
                    break;
                case 2:
                    x = ShapeRect.Right;
                    y = ShapeRect.Y;
                    break;
                case 3:
                    x = ShapeRect.Right;
                    y = ShapeRect.Bottom;
                    break;
                case 4:
                    x = ShapeRect.X;
                    y = ShapeRect.Bottom;
                    break;
            }
            return new Point(x, y);
        }

        public override void MoveHandleTo(Point point, int handleNumber)
        {
            int left = ShapeRect.Left;
            int top = ShapeRect.Top;
            int right = ShapeRect.Right;
            int bottom = ShapeRect.Bottom;
            switch(handleNumber)
            {
                case 1:
                    break;
                case 2:
                    if ((point.X - left) > 10)
                        right = point.X;
                    top = point.Y;
                    break;
                case 3:
                    if ((point.X - left) > 10)
                        right = point.X;
                    bottom = point.Y;
                    break;
                case 4:
                    break;
            }
            SetRectangle(left, top, right - left, bottom - top);
        }
    }
}