using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace WpfApplication
{
    public class Win32WindowWrapper : HwndHost
    {
        private IntPtr hwndControl;

        public Win32WindowWrapper()
        {
            var init = Initialize();
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            hwndControl = CreateControl( hwndParent.Handle );

            return new HandleRef(this, hwndControl);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            DestroyWindow(hwnd.Handle);
        }

        [DllImport("Win32WindowControl.dll", CallingConvention = CallingConvention.StdCall)]
        extern static int Initialize();

        [DllImport("Win32WindowControl.dll", CallingConvention = CallingConvention.StdCall)]
        extern static IntPtr CreateControl(IntPtr parent);

        [DllImport("user32.dll", EntryPoint = "DestroyWindow", CharSet = CharSet.Unicode)]
        internal static extern bool DestroyWindow(IntPtr hwnd);
    }
}
