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
using System.Globalization;
using ICSharpCode.Reporting.PageBuilder.ExportColumns;

namespace ICSharpCode.Reporting.Globals
{
	/// <summary>
	/// Description of StandardFormatter.
	/// </summary>
	class StandardFormatter
	{
		public static void FormatOutput (IExportText textColumn) {
			if (!String.IsNullOrEmpty(textColumn.FormatString)) {
				TypeCode typeCode = TypeHelper.TypeCodeFromString(textColumn.DataType);
				textColumn.Text = FormatItem(textColumn.Text,textColumn.FormatString,typeCode);
			}
		}
	
		/*
		public static string FormatOutput(string valueToFormat,string format,
		                                     string dataType, string nullValue )
		{
			if (String.IsNullOrEmpty(format)) {
				return valueToFormat;
			}
			
			if (String.IsNullOrEmpty(valueToFormat)) {
				return nullValue;
			}
			
			TypeCode typeCode = TypeHelper.TypeCodeFromString(dataType);
			return FormatItem(valueToFormat,format,typeCode,nullValue);                                    
		}
		*/
		
//		private static string FormatItem (string valueToFormat,string format,
//		                         TypeCode typeCode,string nullValue)
		static string FormatItem (string valueToFormat,string format,
		                         TypeCode typeCode)	
		{
			string retValue = String.Empty;
			
			switch (typeCode) {
				case TypeCode.Int16:
				case TypeCode.Int32:
					retValue = FormatIntegers (valueToFormat,format);
					break;
				case TypeCode.DateTime:
					retValue = FormatDate(valueToFormat,format);
					break;
				case TypeCode.Boolean:
					retValue = FormatBool (valueToFormat);
					break;
				case TypeCode.Decimal:
					retValue = FormatDecimal (valueToFormat,format);
					break;
					
				case TypeCode.Double:
				case TypeCode.Single:
					break;
					
				case TypeCode.String:
				case TypeCode.Char:
					retValue = valueToFormat;
					break;
				default:
					retValue = valueToFormat;
					break;
			}
			
			return retValue;
		}
		
		
		static string FormatBool (string toFormat)
		{
			if (CheckValue(toFormat)) {
				bool b = bool.Parse (toFormat);
				return b.ToString (CultureInfo.CurrentCulture);
			}
			return toFormat;
		}
	
		
		static string FormatIntegers(string toFormat, string format)
		{
			string str = String.Empty;
			if (CheckValue (toFormat)) {
				int number = Int32.Parse(toFormat, System.Globalization.NumberStyles.Any, CultureInfo.CurrentCulture.NumberFormat);
				str = number.ToString(format, CultureInfo.CurrentCulture);
				return str;
			} else {
				str = (0.0M).ToString(CultureInfo.CurrentCulture);
			}
			return str;
		}
		
		
		static string FormatDecimal(string toFormat, string format)
		{
			string str = String.Empty;
			if (CheckValue (toFormat)) {
				try {
					decimal dec =	Decimal.Parse(toFormat,
					                            System.Globalization.NumberStyles.Any,
					                            CultureInfo.CurrentCulture.NumberFormat);
					str = dec.ToString (format,CultureInfo.CurrentCulture);
					
				} catch (FormatException) {
					throw ;
				}
				return str;
			} else {
				str = (0.0M).ToString(CultureInfo.CurrentCulture);
			}
			return str;
		}
		
//		http://stackoverflow.com/questions/4710455/i-need-code-to-validate-any-time-in-c-sharp-in-hhmmss-format
		
		static string FormatDate(string toFormat, string format)
		{
			DateTime date;
			if (DateTime.TryParse(toFormat, out date))
			{
				string str = date.ToString(format,
				                           DateTimeFormatInfo.CurrentInfo);
				return str.Trim();
			}

			TimeSpan time;
			bool valid = TimeSpan.TryParseExact(toFormat,
			                                    "g",
			                                    CultureInfo.CurrentCulture,
			                                    out time);
			if (valid) {
				return time.ToString("g",DateTimeFormatInfo.CurrentInfo);
			}
			return toFormat;
		}
		
		
		static bool CheckValue (string toFormat)
		{
			if (String.IsNullOrEmpty(toFormat)) {
				return false;
			}
			return true;
		}
	}
}
