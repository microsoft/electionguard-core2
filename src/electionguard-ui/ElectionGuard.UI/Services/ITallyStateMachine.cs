﻿namespace ElectionGuard.UI.Services;

internal interface ITallyStateMachine

{
    TallyState CurrentState { get; }
    string TallyId { get; set; }
    string ElectionId { get; set; }
    string UserId { get; set; }
    Task Run(bool isAdmin = false);
}