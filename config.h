#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[] =
   "-*-stlarch-medium-r-*-*-10-*-*-*-*-*-*-*" ","
   "-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";

#define NUMCOLORS 8
static const char colors[NUMCOLORS][ColLast][9] = {
   /* border   foreground  background */
   {"#212121", "#696969", "#121212"},   /* 0 = normal   */
   {"#212121", "#E0E0E0", "#121212"},   /* 1 = selected */
   {"#212121", "#4586de", "#121212"},   /* 2 = urgent   */
   {"#212121", "#7bde45", "#121212"},   /* 3 = green    */
   {"#212121", "#fedd26", "#121212"},   /* 4 = yellow   */
   {"#212121", "#e55555", "#121212"},   /* 5 = cyan     */
   {"#212121", "#006699", "#121212"},   /* 6 = magenta  */
   {"#212121", "#C0C0C0", "#121212"},   /* 7 = grey     */
};

static const unsigned int borderpx = 1; /* border pixel of windows   */
static const unsigned int gappx = 5;    /* gap pixel between windows */
static const unsigned int snap = 8;     /* snap pixel                */
static const Bool showbar = True;       /* False means no bar        */
static const Bool topbar = True;        /* False means bottom bar    */

/* tagging */
static const char *tags[] = { "prod", "dev", "term", "web", "media", "misc" };

static const Rule rules[] = {
   /*WM_CLASS     WM_CLASS WM_NAME
      class        instance title          tags mask   isfloating  monitor */
   {"Chromium", NULL, NULL, 1 << 3, False, -1},
};

/* layout(s) */
static const float mfact = 0.55;        /* factor of master area size [0.05..0.95]         */
static const int nmaster = 1;   /* number of clients in master area                */
static const Bool resizehints = False;  /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
   /* symbol     arrange function */
   {"\uE005", True, tile},
   {"\uE011", False, NULL},
   {"[M]", False, monocle},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] =
   { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],
   "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL
};
static const char *termcmd[] = { "uxterm", NULL };
static const char *browser[] = { "chromium", NULL };

static Key keys[] = {
   /* modifier                     key        function        argument */
   {MODKEY, XK_p, spawn, {.v = dmenucmd}},
   {MODKEY, XK_g, spawn, {.v = browser}},
   {MODKEY, XK_Escape, spawn, SHCMD ("xscreensaver-command -lock")},
   {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
   {0, 0x1008ff02, spawn, SHCMD ("xbacklight -inc 25")},
   {0, 0x1008ff03, spawn, SHCMD ("xbacklight -dec 15")},
   {0, XF86XK_AudioLowerVolume, spawn, SHCMD ("amixer -c 0 set Master 1dB-")},
   {0, XF86XK_AudioRaiseVolume, spawn, SHCMD ("amixer -c 0 set Master 1dB+")},
   {0, XF86XK_AudioMute, spawn, SHCMD ("amixer -c 0 set Master toggle")},
   {MODKEY, XK_b, togglebar, {0}},
   {MODKEY, XK_Right, focusstack, {.i = +1}},
   {MODKEY, XK_Left, focusstack, {.i = -1}},
   {MODKEY, XK_i, incnmaster, {.i = +1}},
   {MODKEY, XK_d, incnmaster, {.i = -1}},
   {MODKEY | ShiftMask, XK_Left, setmfact, {.f = -0.05}},
   {MODKEY | ShiftMask, XK_Right, setmfact, {.f = +0.05}},
   {MODKEY, XK_Return, spawn, {.v = termcmd}},
   {MODKEY, XK_Tab, view, {0}},
   {MODKEY | ShiftMask, XK_c, killclient, {0}},
   {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
   {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
   {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
   {MODKEY, XK_space, setlayout, {0}},
   {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
   {MODKEY, XK_0, view, {.ui = ~0}},
   {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
   {MODKEY, XK_comma, focusmon, {.i = -1}},
   {MODKEY, XK_period, focusmon, {.i = +1}},
   {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
   {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
   TAGKEYS (XK_1, 0)
      TAGKEYS (XK_2, 1)
      TAGKEYS (XK_3, 2)
      TAGKEYS (XK_4, 3)
      TAGKEYS (XK_5, 4)
      TAGKEYS (XK_6, 5)
      TAGKEYS (XK_7, 6)
      TAGKEYS (XK_8, 7)
   TAGKEYS (XK_9, 8) {MODKEY | ControlMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
   /* click                event mask      button          function        argument */
   {ClkLtSymbol, 0, Button1, setlayout, {0}},
   {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
   {ClkWinTitle, 0, Button2, zoom, {0}},
   {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
   {ClkClientWin, MODKEY, Button1, movemouse, {0}},
   {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
   {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
   {ClkTagBar, 0, Button1, view, {0}},
   {ClkTagBar, 0, Button3, toggleview, {0}},
   {ClkTagBar, MODKEY, Button1, tag, {0}},
   {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
