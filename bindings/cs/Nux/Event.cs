// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public enum EventType
    {
        KeyEvent,
        CloseEvent
    }

    public class Event
    {
        public Event(EventType initialEventType)
        {
            _eventType = initialEventType;
        }

        private EventType _eventType;
    }
}
