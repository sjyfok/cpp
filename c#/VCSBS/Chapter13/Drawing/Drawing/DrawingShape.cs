using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Windows.UI;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;
using Windows.UI.Xaml.Controls;

namespace Drawing
{
    abstract class DrawingShape
    {
        protected int size;
        protected int locX = 0;
        protected int locY = 0;
        protected Shape shape = null;

        public DrawingShape(int size)
        {
            this.size = size;
        }

        public void SetLocation(int xCoor, int yCoor)
        {
            this.locX = xCoor;
            this.locY = yCoor;
        }

        public void SetColor(Color color)
        {
            if(shape != null)
            {
                SolidColorBrush brush = new SolidColorBrush(color);
                this.shape.Fill = brush;
            }
        }

        public virtual void Draw(Canvas canvas)
        {
            if (this.shape == null)
                throw new InvalidOperationException("Shape is null");
            this.shape.Height = this.size;
            this.shape.Width = this.size;
            Canvas.SetTop(this.shape, this.locY);
            Canvas.SetLeft(this.shape, this.locX);
            canvas.Children.Add(this.shape);
        }
    }
}
