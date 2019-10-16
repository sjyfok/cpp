using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace VisualGraph
{
    public class DrawEllipse:DrawRectangle
    {
        public DrawEllipse(Point point, VisualGraph drawArea)
        {
            ObjName = drawArea.CreateObjName();
            ShapeRect = new Rectangle(point.X, point.Y, Width, Height);
            ObjectType = Global.DrawType.DrawEllipse;
            GenerateID(Global.DrawType.DrawEllipse);
        }

        public override void Draw(Graphics g, VisualGraph drawArea)
        {
            Pen pen = new Pen(Color, PenWidth);
            g.DrawEllipse(pen, DrawRectangle.GetNormalizedRectangle(ShapeRect));
            pen.Dispose();
        }
    }
}
