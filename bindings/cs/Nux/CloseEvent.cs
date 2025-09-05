// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class CloseEvent : Event
    {
        public CloseEvent(bool initialShouldClose)
            : base(EventType.CloseEvent)
        {
            this.ShouldClose = initialShouldClose;
        }

        public bool ShouldClose { get; set; }
    }
}
