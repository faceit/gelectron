#pragma once


class UiApp : public Storm::Trackable<>
{
    std::uint32_t overlayMagicMsg_ =0;
    std::mutex uilock_;
    WNDPROC oldWndProc_ = nullptr;

    std::atomic<HWND> graphicsWindow_ = false;
    std::atomic<bool> windowFocus_ = false;
    RECT windowClientRect_ = {};

    bool isIntercepting_ = false;

    std::mutex taskLock_;
    std::deque<std::function<void()>> tasks_;

#if ALLOW_ASSOC_SYSIME
    HIMC IMC_ = nullptr;
    HIMC originalIMC_ = nullptr;
#endif

#if AUTO_INPUT_INTERCEPT
    bool isInterceptingMouseAuto_ = false;
#endif

public:
    UiApp();
    ~UiApp();

    bool trySetupGraphicsWindow(HWND window);

    bool setup(HWND window);

    HWND window() const;
    bool windowSetted() const;
    bool windowFocused() const;

    void async(const std::function<void()>& task);

    void toggleInputIntercept();
    void startInputIntercept();
    void stopInputIntercept();


    bool shouldBlockOrginalMouseInput();
    bool shouldBlockOrginalKeyInput();
    bool shouldBlockOrginalCursorViz();

    bool isInterceptingInput();

#if AUTO_INPUT_INTERCEPT
    bool isInterceptingMouseAuto();
    void startAutoIntercept();
    void stopAutoIntercept();

#endif

    bool hookWindow(HWND window);
    void unhookWindow();

    void updateWindowState(HWND window);
    void clearWindowState();

    std::uint32_t gameWidth() const;
    std::uint32_t gameHeight() const;

private:

    static LRESULT WINAPI WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    LRESULT hookWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    bool checkHotkey();

    void _runTask();

    bool _setCusror();
};
