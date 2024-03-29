﻿using System.Globalization;

namespace ElectionGuard.UI.Converters;

internal class BallotUloadPanelConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
    {
        return (BallotUploadPanel)value == (BallotUploadPanel)Enum.Parse(typeof(BallotUploadPanel), (string)parameter);
    }

    public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}
