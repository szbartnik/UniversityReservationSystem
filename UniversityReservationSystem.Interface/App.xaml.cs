﻿using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Navigation;

namespace UniversityReservationSystem.Interface
{
    public partial class App
    {
        [DllImport("UniversityReservationSystem.dll")]
        public static extern bool LoadDB(string filePath);

        [DllImport("UniversityReservationSystem.dll")]
        public static extern bool SaveDB();

        [DllImport("UniversityReservationSystem.dll")]
        private static extern bool FreeDB();

        [DllImport("UniversityReservationSystem.dll")]
        public static extern IntPtr GetGroupByIndex(uint groupIndex);

        [DllImport("UniversityReservationSystem.dll")]
        public static extern uint GetGroupsCount();

        public App()
        {
            LoadDB("home");
        }

        protected override void OnExit(ExitEventArgs e)
        {
            FreeDB();
            base.OnExit(e);
        }
    }
}
