using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace MathsOperators
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void calculateClick(object sender, RoutedEventArgs e)
        {
            try
            {
                if ((bool)addition.IsChecked)
                {
                    addValues();
                }
                else if ((bool)subtraction.IsChecked)
                {
                    subtractValues();
                }
                else if ((bool)multiplication.IsChecked)
                {
                    multiplyValues();
                }
                else if ((bool)division.IsChecked)
                {
                    divideValues();
                }
                else if ((bool)remainder.IsChecked)
                {
                    remainderValues();
                }
                else
                {
                    throw new InvalidOperationException("No operator selected");
                }
            }
            catch (FormatException fex)
            {
                result.Text = fex.Message;
            }
            catch(DivideByZeroException dex)
            {
                result.Text = dex.Message;
            }
            catch (OverflowException oex)
            {
                result.Text = oex.Message;
            }
            catch (InvalidOperationException ioEx)
            {
                result.Text = ioEx.Message;
            }
            catch (Exception ex)
            {
                result.Text = ex.Message;
            }
        }

            private void addValues()
        {
            //try
            //{
                int lhs = int.Parse(lhsOperand.Text);
                int rhs = int.Parse(rhsOperand.Text);
                int outcome = 0;

                outcome = lhs + rhs;
                expression.Text = $"{lhs} + {rhs}";
                result.Text = outcome.ToString();
            //}
            //catch (FormatException fex)
            //{
            //    result.Text = fex.Message;
            //}
        }

        private void subtractValues()
        {
            //try
            //{
                int lhs = int.Parse(lhsOperand.Text);
                int rhs = int.Parse(rhsOperand.Text);
                int outcome = 0;

                outcome = lhs - rhs;
                expression.Text = $"{lhs} - {rhs}";
                result.Text = outcome.ToString();
            //}
            //catch (FormatException fex)
            //{
            //    result.Text = fex.Message;
            //}
        }

        private void multiplyValues()
        {
            //try
            //{

                int lhs = int.Parse(lhsOperand.Text);
                int rhs = int.Parse(rhsOperand.Text);
                int outcome = 0;

                outcome = checked(lhs * rhs);
                expression.Text = $"{lhs} * {rhs}";
                result.Text = outcome.ToString();
            //}
            //catch (FormatException fex)
            //{
            //    result.Text = fex.Message;
            //}
        }

        private void divideValues()
        {
            //try
            //{
                int lhs = int.Parse(lhsOperand.Text);
                int rhs = int.Parse(rhsOperand.Text);
                int outcome = 0;

                outcome = lhs / rhs;
                expression.Text = $"{lhs} / {rhs}";
                result.Text = outcome.ToString();
            //}
            //catch (FormatException fex)
            //{
            //    result.Text = fex.Message;
            //}
        }

        private void remainderValues()
        {
            //try
            //{
                int lhs = int.Parse(lhsOperand.Text);
                int rhs = int.Parse(rhsOperand.Text);
                int outcome = 0;

                outcome = lhs % rhs;
                expression.Text = $"{lhs} % {rhs}";
                result.Text = outcome.ToString();
            //}
            //catch (FormatException fex)
            //{
            //    result.Text = fex.Message;
            //}
        }
    }
}
