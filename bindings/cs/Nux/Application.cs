// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class Application
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet =  CharSet.Unicode)]
        internal static extern IntPtr nux_application_create(int argc, [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPStr)] string[] argv);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern Encoding nux_application_get_encoding();

        [DllImport(Impl.SharedLibraryFilename, CharSet =  CharSet.Unicode)]
        internal static extern int nux_application_run(IntPtr application);

        public Application(string[] args)
        {
            _nux_application_v = nux_application_create(args.Length, args);
            s_instance = this;
        }

        public static Application Instance
        {
            get
            {
                return s_instance;
            }
        }

        public static Encoding Encoding
        {
            get
            {
                return nux_application_get_encoding();
            }
        }

        public int Run()
        {
            return nux_application_run(_nux_application_v);
        }

        private static Application s_instance;

        private IntPtr _nux_application_v;
    }
}
