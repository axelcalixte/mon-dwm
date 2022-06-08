/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int gappx = 3;    /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int swallowfloating =
    0;                        /* 1 means swallow floating windows by default */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const char *fonts[] = {
    "Liga SFMono Nerd "
    "Font:style=Regular:pixelsize=15:autohint=true:antialias=true",
    "Font Awesome 5 Free "
    "Regular:style=Regular:pixelsize=15:antialias=true:autohint=true",
    "Noto Color Emoji:style=Regular:pixelsize=15:antialias=true:autohint=true"};
static const char dmenufont[] = "Liga SFMono Nerd Font:style=Regular:size=11";
static const char col_gray1[] = "#191724"; // default background
static const char col_gray2[] = "#1f1d2e"; // lighter background
static const char col_gray3[] = "#e0def4"; // default foreground
static const char col_gray4[] = "#e0def4"; // default foreground
static const char col_cyan[] = "#286983";  // waveBlue1
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};

static const char *const autostart[] = {
    "aslstatus", NULL, "setxkbmap", "-option", "caps:swapescape", NULL,
    "xcompmgr", "-c", "-C", "-t-5", "-l-5", "-r4.2", "-o.55", "-f", "-I.15",
    "-O.17", "-D3", NULL, "dunst", "-c", "/home/axel/.config/dunst/dunstrc",
    NULL,
    //"picom", "--experimental-backends", NULL,
    "xrdb", "-merge", "/home/axel/.config/x11/.Xresources", NULL, "xautolock",
    "-locker", "slock", "-time", "5", "-corners", "----", NULL, "nitrogen",
    "--restore", NULL, NULL /* terminate */
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal
       noswallow  monitor */
    {"firefox", "Navigator", NULL, 1 << 1, 0, 0, 1, -1},
    {"Chromium-browser", "chromium-browser", NULL, 1 << 1, 0, 0, 1, -1},
    {"KeePassXC", "keepassxc", NULL, 1 << 8, 0, 0, 1, -1},
    {"Claws-mail", "claws-mail", NULL, 1 << 7, 0, 0, 1, -1},
    {"discord", "discord", NULL, 1 << 4, 0, 0, 1, -1},
    {"TelegramDesktop", "telegram-desktop", NULL, 1 << 5, 0, 0, 1, -1},
    {"Signal", "signal", NULL, 1 << 5, 0, 0, 1, -1},
    {"KeePassXC", "keepassxc", "Unlock Database - KeePassXC", 1 << 8, 1, 0, 1,
     -1},
    {NULL, NULL, "xdg-su: /sbin/yast2", 0, 1, 1, 1, -1},
    {NULL, NULL, "xdg-su: /sbin/yast2 sw_single ", 0, 1, 1, 1, -1},
    {"kitty", NULL, NULL, 1 << 0, 0, 1, 0, -1},
    {"St", NULL, NULL, 0, 0, 1, 0, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1}, /* xev */
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"kitty", NULL};
static const char *web[] = {"firefox", NULL};
static const char *filemanager[] = {"st", "-e", "nnn", "-C", NULL};
static const char *htop[] = {"st", "-e", "htop", NULL};
static const char *keepass[] = {"keepassxc", NULL};
static const char *musicplayer[] = {"st", "-e", "cmus", NULL};
static const char *mixer[] = {"st", "-e", "pulsemixer", NULL};
static const char *mail[] = {"claws-mail", "--alternate-config-dir",
                             "/home/axel/.config/claws-mail", NULL};
static const char *bluetoothctl[] = {"st", "-e", "bluetoothctl", NULL};

/* commands spawned when clicking statusbar, the mouse button pressed is
 * exported as BUTTON */
static const StatusCmd statuscmds[] = {
    {"sudo zypper dup", 1},
    {"/home/axel/.local/bin/scripts/weather.sh", 2},
    {"pulsemixer", 3},
    {"pamixer --source $(pamixer --list-sources | tail -1 | cut -d' ' -f1) -t",
     4},
    {"sudo nmtui", 5},
    {"cal", 6},
};
static const char *statuscmd[] = {"/bin/sh", "-c", NULL, NULL};

#include <X11/XF86keysym.h>
static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {Mod1Mask | ShiftMask, XK_w, spawn, {.v = web}},
    {Mod1Mask | ShiftMask, XK_f, spawn, {.v = filemanager}},
    {Mod1Mask | ShiftMask, XK_h, spawn, {.v = htop}},
    {Mod1Mask | ShiftMask, XK_k, spawn, {.v = keepass}},
    {Mod1Mask | ShiftMask, XK_m, spawn, {.v = musicplayer}},
    {Mod1Mask | ShiftMask, XK_p, spawn, {.v = mixer}},
    {Mod1Mask | ShiftMask, XK_c, spawn, {.v = mail}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_agrave, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_agrave, tag, {.ui = ~0}},
    {MODKEY, XK_ugrave, focusmon, {.i = -1}},
    {MODKEY, XK_asterisk, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_ugrave, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_asterisk, tagmon, {.i = +1}},
    TAGKEYS(XK_ampersand, 0) TAGKEYS(XK_eacute, 1) TAGKEYS(XK_quotedbl, 2)
        TAGKEYS(XK_apostrophe, 3) TAGKEYS(XK_parenleft, 4) TAGKEYS(XK_minus, 5)
            TAGKEYS(XK_egrave, 6) TAGKEYS(XK_underscore, 7) TAGKEYS(
                XK_ccedilla, 8){MODKEY | ShiftMask, XK_q, spawn,
                                SHCMD("~/.local/bin/scripts/poweroff.sh")},
    {MODKEY, XK_a, spawn, SHCMD("~/.local/bin/scripts/switch")},
    {MODKEY | ShiftMask, XK_Delete, quit, {0}},

    /* Function keys */
    {0, XF86XK_AudioMute, spawn, SHCMD("pamixer -t")},
    {0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer -i5")},
    {0, XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer -d5")},
    {0, XF86XK_AudioMicMute, spawn,
     SHCMD("pamixer --source $(pamixer --list-sources | tail -1 | cut -d' ' "
           "-f1) -t")},
    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl -e s +5%")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl -e s 5%-")},
    {0, XF86XK_Display, spawn, SHCMD("~/.local/bin/scripts/screens.sh")},
    //{ 0, XF86XK_Tools,	        spawn,		SHCMD("") },
    {0, XF86XK_Bluetooth, spawn, {.v = bluetoothctl}},
    //{ 0, XF86XK_Wakeup,       	spawn,		SHCMD("") },
    {0, XF86XK_Favorites, spawn, SHCMD("~/.local/bin/scripts/weather.sh")},
    {Mod1Mask | ShiftMask, XK_t, spawn,
     SHCMD("tmux list-session | dmenu -l 5 | cut -d':' -f1 | xargs tmux "
           "kill-session -t")},
    //{Mod1Mask | ShiftMask, XK_a, spawn,SHCMD("t=$(tmux list-session | dmenu -l
    // 5 | cut -d':' -f1); st -e 'tmux attach-session -t $t'")},
    {MODKEY, XK_w, spawn,
     SHCMD(
         "w=$(echo '' | dmenu -p 'web search'); case '$w' in '' ) exit 0 ;; * "
         ") firefox 'https://duckduckgo.com/?q='$w'';; esac")},

    /* CMUS music control */
    {MODKEY, XK_Right, spawn, SHCMD("cmus-remote --next")},
    {MODKEY, XK_Left, spawn, SHCMD("cmus-remote --prev")},
    {MODKEY, XK_Up, spawn, SHCMD("cmus-remote --pause")},
    {MODKEY, XK_Down, spawn, SHCMD("cmus-remote --stop")},

    /* Screenshots */
    {MODKEY, XK_Print, spawn,
     SHCMD("maim -s | xclip -selection clipboard -t image/png")},
    {MODKEY | ShiftMask, XK_Print, spawn,
     SHCMD("maim ~/pics/maim-$(date +%s).png -s | xclip -selection clipboard "
           "-t image/png")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button1, spawn, {.v = statuscmd}},
    {ClkStatusText, 0, Button2, spawn, {.v = statuscmd}},
    {ClkStatusText, 0, Button3, spawn, {.v = statuscmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkRootWin, 0, Button3, spawn,
     SHCMD("~/.local/bin/scripts/xdg-xmenu.sh > ~/.cache/menu; xmenu < "
           "~/.cache/menu | sh &")},
};
