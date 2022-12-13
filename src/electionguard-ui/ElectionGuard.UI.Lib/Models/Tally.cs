﻿using CommunityToolkit.Mvvm.ComponentModel;

namespace ElectionGuard.UI.Lib.Models;

public partial class Tally : BaseModel<Tally>
{
    private readonly static string table = "tallies";

    public Tally() : base(table)
    {
    }

    [ObservableProperty]
    private string? _name;

}

