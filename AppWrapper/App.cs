using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;
using GraphicCore;
using Windows.Graphics.Display;
using Windows.ApplicationModel.Activation;
using Windows.UI.ViewManagement;
using Windows.Foundation;

namespace AppWrapper
{

    public class App : IFrameworkView
    {

        private bool Exit;
        private bool Visible;
        private bool InSizeMove;
        private float DPI;
        private float LogicalWidth;
        private float LogicalHeight;
        private DisplayOrientations NativeOrientation;
        private DisplayOrientations CurrentOrientation;
        private Game Game;

        public App()
        {
            this.Exit = false;
            this.Visible = true;
            this.InSizeMove = false;
            this.DPI = 96f;
            this.LogicalWidth = 800f;
            this.LogicalHeight = 600f;
            this.NativeOrientation = DisplayOrientations.None;
            this.CurrentOrientation = DisplayOrientations.None;
        }

        public void Initialize(CoreApplicationView applicationView)
        {
            applicationView.Activated += OnActivated;
            CoreApplication.Suspending += OnSuspending;
            CoreApplication.Resuming += OnResuming;

            this.Game = new Game();
        }

        public void SetWindow(CoreWindow window)
        {
            window.SizeChanged += OnWindowSizeChanged;

            try
            {
                window.ResizeStarted += OnResizeStarted;
                window.ResizeCompleted += OnResizeCompleted;
            }
            catch (Exception) { }

            window.VisibilityChanged += OnVisibilityChanged;
            window.Closed += OnWindowClosed;

            var dispatcher = CoreWindow.GetForCurrentThread().Dispatcher;
            dispatcher.AcceleratorKeyActivated += OnAcceleratorKeyActivated;

            var navigation = Windows.UI.Core.SystemNavigationManager.GetForCurrentView();
            navigation.BackRequested += OnBackRequested;

            var currentDisplayInformation = DisplayInformation.GetForCurrentView();
            currentDisplayInformation.DpiChanged += OnDpiChanged;
            currentDisplayInformation.OrientationChanged += OnOrientationChanged;

            DisplayInformation.DisplayContentsInvalidated += OnDisplayContentsInvalidated;

            this.DPI = currentDisplayInformation.LogicalDpi;

            this.LogicalHeight = (float)window.Bounds.Height;
            this.LogicalWidth = (float)window.Bounds.Width;

            this.NativeOrientation = currentDisplayInformation.NativeOrientation;
            this.CurrentOrientation = currentDisplayInformation.CurrentOrientation;

            int outputWidth = ConvertDipsToPixels(this.LogicalWidth);
            int outputHeight = ConvertDipsToPixels(this.LogicalHeight);

            int rotation = ComputeDisplayRotation();

            if (rotation == 2 || rotation == 4)
            {
                var tmp = outputHeight;
                outputHeight = outputWidth;
                outputWidth = tmp;
            }

            this.Game.Initialize(window, outputWidth, outputHeight, rotation);
        }

        public void Load(string entryPoint) { }

        public void Run()
        {
            while (!this.Exit)
            {
                if (this.Visible)
                {
                    this.Game.Tick();

                    CoreWindow.GetForCurrentThread().Dispatcher.ProcessEvents(CoreProcessEventsOption.ProcessAllIfPresent);
                }
                else
                    CoreWindow.GetForCurrentThread().Dispatcher.ProcessEvents(CoreProcessEventsOption.ProcessOneAndAllPending);
            }
        }

        public void Uninitialize()
        {
            
        }

        private void OnActivated(CoreApplicationView sender, Windows.ApplicationModel.Activation.IActivatedEventArgs args)
        {
            if (args.Kind == ActivationKind.Launch)
            {
                var launchArgs = (LaunchActivatedEventArgs)args;

                if (launchArgs.PrelaunchActivated)
                {
                    CoreApplication.Exit();
                    return;
                }
            }

            int w, h;
            w = this.Game.GetDefaultWidth();
            h = this.Game.GetDefaultHeight();

            this.DPI = DisplayInformation.GetForCurrentView().LogicalDpi;

            ApplicationView.PreferredLaunchWindowingMode = ApplicationViewWindowingMode.PreferredLaunchViewSize;

            var desiredSize = new Size(ConvertPixelsToDips(w), ConvertPixelsToDips(h));
            ApplicationView.PreferredLaunchViewSize = desiredSize;

            var view = ApplicationView.GetForCurrentView();
            var minSize = new Size(ConvertPixelsToDips(320), ConvertPixelsToDips(200));

            view.SetPreferredMinSize(minSize);

            CoreWindow.GetForCurrentThread().Activate();

            view.FullScreenSystemOverlayMode = FullScreenSystemOverlayMode.Standard;
            view.TryResizeView(desiredSize);
        }

        private void OnResuming(object sender, object e)
        {
            this.Game.OnResuming();
        }

        private void OnSuspending(object sender, Windows.ApplicationModel.SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            Task.Run(() =>
            {
                this.Game.OnSuspending();
                deferral.Complete();
            });
        }

        private void OnResizeCompleted(CoreWindow sender, object args)
        {
            this.InSizeMove = false;

            HandleWindowSizeChanged();
        }

        private void OnResizeStarted(CoreWindow sender, object args)
        {
            this.InSizeMove = true;
        }

        private void OnWindowSizeChanged(CoreWindow sender, WindowSizeChangedEventArgs args)
        {
            this.LogicalWidth = (float)sender.Bounds.Width;
            this.LogicalHeight = (float)sender.Bounds.Height;

            if (this.InSizeMove)
                return;

            HandleWindowSizeChanged();
        }

        private void OnDisplayContentsInvalidated(DisplayInformation sender, object args)
        {
            this.Game.ValidateDevice();
        }

        private void OnOrientationChanged(DisplayInformation sender, object args)
        {
            var resizeManager = CoreWindowResizeManager.GetForCurrentView();
            resizeManager.ShouldWaitForLayoutCompletion = true;

            this.CurrentOrientation = sender.CurrentOrientation;

            HandleWindowSizeChanged();

            resizeManager.NotifyLayoutCompleted();
        }

        private void OnDpiChanged(DisplayInformation sender, object args)
        {
            this.DPI = sender.LogicalDpi;

            HandleWindowSizeChanged();
        }

        private void OnBackRequested(object sender, BackRequestedEventArgs e)
        {
            e.Handled = true;
        }

        private void OnAcceleratorKeyActivated(CoreDispatcher sender, AcceleratorKeyEventArgs args)
        {
            if (args.EventType == CoreAcceleratorKeyEventType.SystemKeyDown
                && args.VirtualKey == Windows.System.VirtualKey.Enter
                && args.KeyStatus.IsMenuKeyDown
                && !args.KeyStatus.WasKeyDown)
            {
                var view = ApplicationView.GetForCurrentView();
                if (view.IsFullScreenMode)
                    view.ExitFullScreenMode();
                else
                    view.TryEnterFullScreenMode();

                args.Handled = true;
            }
        }

        private void OnWindowClosed(CoreWindow sender, CoreWindowEventArgs args)
        {
            this.Exit = true;
        }

        private void OnVisibilityChanged(CoreWindow sender, VisibilityChangedEventArgs args)
        {
            this.Visible = args.Visible;
            if (this.Visible)
                this.Game.OnActivated();
            else
                this.Game.OnDeactivated();
        }

        private int ConvertDipsToPixels(float dips)
        {
            return (int)(dips * this.DPI / 96f + 0.5f);
        }

        private float ConvertPixelsToDips(int pixels)
        {
            return (float)(pixels) * 96f / this.DPI;
        }

        private int ComputeDisplayRotation()
        {
            switch (this.NativeOrientation)
            {
                case DisplayOrientations.Landscape:
                    switch (this.CurrentOrientation)
                    {
                        case DisplayOrientations.Landscape:
                            return 1;
                        case DisplayOrientations.Portrait:
                            return 4;
                        case DisplayOrientations.LandscapeFlipped:
                            return 3;
                        case DisplayOrientations.PortraitFlipped:
                            return 2;
                    }
                    break;
                case DisplayOrientations.Portrait:
                    switch (this.CurrentOrientation)
                    {
                        case DisplayOrientations.Landscape:
                            return 2;
                        case DisplayOrientations.Portrait:
                            return 1;
                        case DisplayOrientations.LandscapeFlipped:
                            return 4;
                        case DisplayOrientations.PortraitFlipped:
                            return 3;
                    }
                    break;
            }
            return -1;
        }
        
        private void HandleWindowSizeChanged()
        {
            int outputWidth = ConvertDipsToPixels(this.LogicalWidth);
            int outputHeight = ConvertDipsToPixels(this.LogicalHeight);

            int rotation = ComputeDisplayRotation();

            if (rotation == 2 || rotation == 4)
            {
                var tmp = outputHeight;
                outputHeight = outputWidth;
                outputWidth = tmp;
            }

            this.Game.OnWindowSizeChanged(outputWidth, outputHeight, rotation);
        }
    }

    public class AppFactory : IFrameworkViewSource
    {
        public IFrameworkView CreateView()
        {
            return new App();
        }

        public static void Main(string[] args)
        {
            var appFacotry = new AppFactory();
            CoreApplication.Run(appFacotry);
        }

        public static void ExitGame()
        {
            Windows.ApplicationModel.Core.CoreApplication.Exit();
        }
    }
}
