// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    internal static class Impl
    {
        internal const string SharedLibraryFilename = "libnux16c";

        internal static byte[] ToNuxString(string input)
        {
            if (string.IsNullOrEmpty(input))
            {
                return new byte[] { 0 };
            }
            return Application.Encoding == Encoding.Utf16
                ? System.Text.Encoding.Unicode.GetBytes(input + "\0")
                : System.Text.Encoding.UTF8.GetBytes(input + "\0")
            ;
        }

        internal static string ToSystemString(IntPtr data, int size)
        {
            return Application.Encoding == Encoding.Utf16
                ? Marshal.PtrToStringUni(data, size)
                : Marshal.PtrToStringAnsi(data, size)
            ;
        }
    }
}
