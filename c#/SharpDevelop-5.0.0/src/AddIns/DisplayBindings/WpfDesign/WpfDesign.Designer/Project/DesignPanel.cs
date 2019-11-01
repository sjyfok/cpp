﻿// Copyright (c) 2014 AlphaSierraPapa for the SharpDevelop Team
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
// to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Threading;

using ICSharpCode.WpfDesign.Adorners;
using ICSharpCode.WpfDesign.Designer.Controls;
using ICSharpCode.WpfDesign.Designer.Xaml;

namespace ICSharpCode.WpfDesign.Designer
{
	public sealed class DesignPanel : Decorator, IDesignPanel, INotifyPropertyChanged
	{
		#region Hit Testing
		
		private List<DependencyObject> hitTestElements = new List<DependencyObject>();
		private DependencyObject lastElement;
		
		/// <summary>
		/// this element is always hit (unless HitTestVisible is set to false)
		/// </summary>
		sealed class EatAllHitTestRequests : UIElement
		{
			protected override GeometryHitTestResult HitTestCore(GeometryHitTestParameters hitTestParameters)
			{
				return new GeometryHitTestResult(this, IntersectionDetail.FullyContains);
			}
			
			protected override HitTestResult HitTestCore(PointHitTestParameters hitTestParameters)
			{
				return new PointHitTestResult(this, hitTestParameters.HitPoint);
			}
		}
		
		void RunHitTest(Visual reference, Point point, HitTestFilterCallback filterCallback, HitTestResultCallback resultCallback)
		{
			VisualTreeHelper.HitTest(reference, filterCallback, resultCallback,
				new PointHitTestParameters(point));
		}
		
		HitTestFilterBehavior FilterHitTestInvisibleElements(DependencyObject potentialHitTestTarget)
		{
			UIElement element = potentialHitTestTarget as UIElement;
						
			if (element != null) {
				if (!(element.IsHitTestVisible && element.Visibility == Visibility.Visible)) {
					return HitTestFilterBehavior.ContinueSkipSelfAndChildren;
				}
				
				var designItem = Context.Services.Component.GetDesignItem(element) as XamlDesignItem;
			
				if (designItem != null && designItem.IsDesignTimeLocked) {
					return HitTestFilterBehavior.ContinueSkipSelfAndChildren;
				}			
			}
			
			hitTestElements.Add(element);
						
			return HitTestFilterBehavior.Continue;
		}
		
		/// <summary>
		/// Performs a custom hit testing lookup for the specified mouse event args.
		/// </summary>
		public DesignPanelHitTestResult HitTest(Point mousePosition, bool testAdorners, bool testDesignSurface, HitTestType hitTestType)
		{
			hitTestElements.Clear();
			
			DesignPanelHitTestResult result = DesignPanelHitTestResult.NoHit;
			HitTest(mousePosition, testAdorners, testDesignSurface,
				delegate(DesignPanelHitTestResult r) {
					result = r;
					return false;
				}, hitTestType);
			
			return result;
		}
		
		/// <summary>
		/// Performs a hit test on the design surface, raising <paramref name="callback"/> for each match.
		/// Hit testing continues while the callback returns true.
		/// </summary>
		public void HitTest(Point mousePosition, bool testAdorners, bool testDesignSurface, Predicate<DesignPanelHitTestResult> callback, HitTestType hitTestType)
		{
			if (mousePosition.X < 0 || mousePosition.Y < 0 || mousePosition.X > this.RenderSize.Width || mousePosition.Y > this.RenderSize.Height) {
				return;
			}
			// First try hit-testing on the adorner layer.

			bool continueHitTest = true;

			HitTestFilterCallback filterBehavior = CustomHitTestFilterBehavior ?? FilterHitTestInvisibleElements;
			CustomHitTestFilterBehavior = null;
			hitTestElements.Clear();
			
			if (testAdorners) {

				RunHitTest(
					_adornerLayer, mousePosition, filterBehavior,
					delegate(HitTestResult result) {
						if (result != null && result.VisualHit != null && result.VisualHit is Visual) {
							DesignPanelHitTestResult customResult = new DesignPanelHitTestResult((Visual)result.VisualHit);
							DependencyObject obj = result.VisualHit;
							while (obj != null && obj != _adornerLayer) {
								AdornerPanel adorner = obj as AdornerPanel;
								if (adorner != null) {
									customResult.AdornerHit = adorner;
								}
								obj = VisualTreeHelper.GetParent(obj);
							}
							continueHitTest = callback(customResult);
							return continueHitTest ? HitTestResultBehavior.Continue : HitTestResultBehavior.Stop;
						} else {
							return HitTestResultBehavior.Continue;
						}
					});
			}

			if (continueHitTest && testDesignSurface) {
				RunHitTest(
					this.Child, mousePosition, filterBehavior,
					delegate(HitTestResult result) {
						if (result != null && result.VisualHit != null && result.VisualHit is Visual) {
							DesignPanelHitTestResult customResult = new DesignPanelHitTestResult((Visual)result.VisualHit);

							ViewService viewService = _context.Services.View;
							DependencyObject obj = result.VisualHit;
							
							if (hitTestType == HitTestType.ElementSelection)
							{
								if (Keyboard.IsKeyDown(Key.LeftAlt))
								if (lastElement != null && lastElement != _context.RootItem.Component &&
									hitTestElements.Contains(lastElement))
								{
									var idx = hitTestElements.IndexOf(lastElement) - 1;
									if (idx >= 0)
										obj = hitTestElements[idx];
								}
							}
							
							while (obj != null) {
								if ((customResult.ModelHit = viewService.GetModel(obj)) != null)
									break;
								obj = VisualTreeHelper.GetParent(obj);
							}
							if (customResult.ModelHit == null) {
								customResult.ModelHit = _context.RootItem;
							}
							
							if (hitTestType == HitTestType.ElementSelection)
							{
								lastElement = obj;
							}
							
							
							continueHitTest = callback(customResult);
							return continueHitTest ? HitTestResultBehavior.Continue : HitTestResultBehavior.Stop;
						} else {
							return HitTestResultBehavior.Continue;
						}
					}
				);
			}
		}
		#endregion
		
		#region Fields + Constructor
		DesignContext _context;
		readonly EatAllHitTestRequests _eatAllHitTestRequests;
		readonly AdornerLayer _adornerLayer;
		
		public DesignPanel()
		{
			this.Focusable = true;
			this.Margin = new Thickness(16);
			DesignerProperties.SetIsInDesignMode(this, true);
			
			_eatAllHitTestRequests = new EatAllHitTestRequests();
			_eatAllHitTestRequests.MouseDown += delegate {
				// ensure the design panel has focus while the user is interacting with it
				this.Focus();
			};
			_eatAllHitTestRequests.AllowDrop = true;
			_adornerLayer = new AdornerLayer(this);
			
			this.PreviewKeyUp += DesignPanel_KeyUp;
			this.PreviewKeyDown += DesignPanel_KeyDown;
		}
		#endregion
		
		#region Properties
		
		//Set custom HitTestFilterCallbak
		public HitTestFilterCallback CustomHitTestFilterBehavior { get; set; }
		/// <summary>
		/// Gets/Sets the design context.
		/// </summary>
		public DesignContext Context {
			get { return _context; }
			set { _context = value; }
		}
		
		public ICollection<AdornerPanel> Adorners {
			get {
				return _adornerLayer.Adorners;
			}
		}
		
		/// <summary>
		/// Gets/Sets if the design content is visible for hit-testing purposes.
		/// </summary>
		public bool IsContentHitTestVisible {
			get { return !_eatAllHitTestRequests.IsHitTestVisible; }
			set { _eatAllHitTestRequests.IsHitTestVisible = !value; }
		}
		
		/// <summary>
		/// Gets/Sets if the adorner layer is visible for hit-testing purposes.
		/// </summary>
		public bool IsAdornerLayerHitTestVisible {
			get { return _adornerLayer.IsHitTestVisible; }
			set { _adornerLayer.IsHitTestVisible = value; }
		}
		
		/// <summary>
		/// Enables / Disables the Snapline Placement
		/// </summary>
		private bool _useSnaplinePlacement = true;
		public bool UseSnaplinePlacement {
			get { return _useSnaplinePlacement; }
			set {
				if (_useSnaplinePlacement != value) {
					_useSnaplinePlacement = value;
					OnPropertyChanged("UseSnaplinePlacement");
				}
			}
		}
		
		/// <summary>
		/// Enables / Disables the Raster Placement
		/// </summary>
		private bool _useRasterPlacement = false;
		public bool UseRasterPlacement {
			get { return _useRasterPlacement; }
			set {
				if (_useRasterPlacement != value) {
					_useRasterPlacement = value;
					OnPropertyChanged("UseRasterPlacement");
				}
			}
		}
		
		/// <summary>
		/// Sets the with of the Raster when using Raster Placement
		/// </summary>
		private int _rasterWidth = 5;
		public int RasterWidth {
			get { return _rasterWidth; }
			set {
				if (_rasterWidth != value) {
					_rasterWidth = value;
					OnPropertyChanged("RasterWidth");
				}
			}
		}
		
		#endregion
		
		#region Visual Child Management
		public override UIElement Child {
			get { return base.Child; }
			set {
				if (base.Child == value)
					return;
				if (value == null) {
					// Child is being set from some value to null
					
					// remove _adornerLayer and _eatAllHitTestRequests
					RemoveVisualChild(_adornerLayer);
					RemoveVisualChild(_eatAllHitTestRequests);
				} else if (base.Child == null) {
					// Child is being set from null to some value
					AddVisualChild(_adornerLayer);
					AddVisualChild(_eatAllHitTestRequests);
				}
				base.Child = value;
			}
		}
		
		protected override Visual GetVisualChild(int index)
		{
			if (base.Child != null) {
				if (index == 0)
					return base.Child;
				else if (index == 1)
					return _eatAllHitTestRequests;
				else if (index == 2)
					return _adornerLayer;
			}
			return base.GetVisualChild(index);
		}
		
		protected override int VisualChildrenCount {
			get {
				if (base.Child != null)
					return 3;
				else
					return base.VisualChildrenCount;
			}
		}
		
		protected override Size MeasureOverride(Size constraint)
		{
			Size result = base.MeasureOverride(constraint);
			if (this.Child != null) {
				_adornerLayer.Measure(constraint);
				_eatAllHitTestRequests.Measure(constraint);
			}
			return result;
		}
		
		protected override Size ArrangeOverride(Size arrangeSize)
		{
			Size result = base.ArrangeOverride(arrangeSize);
			if (this.Child != null) {
				Rect r = new Rect(new Point(0, 0), arrangeSize);
				_adornerLayer.Arrange(r);
				_eatAllHitTestRequests.Arrange(r);
			}
			return result;
		}
		#endregion
		
		PlacementOperation placementOp;
		int dx = 0;
		int dy = 0;
		
		private void DesignPanel_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.Key == Key.Left || e.Key == Key.Right || e.Key == Key.Up || e.Key == Key.Down)
			{
				e.Handled = true;
				
				if (placementOp != null) {
					placementOp.Commit();
					placementOp = null;
				}
			}
		}
		
		void DesignPanel_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.Key == Key.Left || e.Key == Key.Right || e.Key == Key.Up || e.Key == Key.Down) {
				e.Handled = true;
				
				if (placementOp == null) {
					dx = 0;
					dy = 0;
					placementOp = PlacementOperation.Start(Context.Services.Selection.SelectedItems, PlacementType.Move);
				}
				
				switch (e.Key) {
					case Key.Left:
						dx += Keyboard.IsKeyDown(Key.LeftShift) ? -10 : -1;
						break;
					case Key.Up:
						dy += Keyboard.IsKeyDown(Key.LeftShift) ? -10 : -1;
						break;
					case Key.Right:
						dx += Keyboard.IsKeyDown(Key.LeftShift) ? 10 : 1;
						break;
					case Key.Down:
						dy += Keyboard.IsKeyDown(Key.LeftShift) ? 10 : 1;
						break;
				}
				
				foreach (PlacementInformation info in placementOp.PlacedItems)
				{
					var bounds = info.OriginalBounds;
					
					if (!Keyboard.IsKeyDown(Key.LeftCtrl)) {
						info.Bounds = new Rect(bounds.Left + dx,
							bounds.Top + dy,
							bounds.Width,
							bounds.Height);
					} else {
						if (info.OriginalBounds.Width + dx >= 0 && info.OriginalBounds.Height + dy >= 0)  {
							info.Bounds = new Rect(info.OriginalBounds.Left,
							                       info.OriginalBounds.Top,
							                       info.OriginalBounds.Width + dx,
							                       info.OriginalBounds.Height + dy);
						}
					}
					
					placementOp.CurrentContainerBehavior.SetPosition(info);
				}
			}
		}
		
		static bool IsPropertySet(UIElement element, DependencyProperty d)
        {
            return element.ReadLocalValue(d) != DependencyProperty.UnsetValue;
        }
		
		protected override void OnQueryCursor(QueryCursorEventArgs e)
		{
			base.OnQueryCursor(e);
			if (_context != null) {
				Cursor cursor = _context.Services.Tool.CurrentTool.Cursor;
				if (cursor != null) {
					e.Cursor = cursor;
					e.Handled = true;
				}
			}
		}
		
		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged(string propertyName)
		{
			PropertyChangedEventHandler handler = PropertyChanged;
			if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
		}
	}
}
