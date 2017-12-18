/* See LICENSE file for copyright and license details. */

/* appearance */
#include "movestack.c"
static const char *fonts[]    = { "Wuncon Siji:size=10", "xos4 Terminus:size=9" };
static const char dmenufont[] = "xos4 Terminus:size=9";

static const char normbordercolor[] = "#212121";
static const char selbordercolor[]  = "#212121";
static const char normbgcolor[]     = "#1C1C1C";
static const char normfgcolor[]     = "#C0C0C0";
static const char selbgcolor[]      = "#111111";
static const char selfgcolor[]      = "#FDFDFD";

static const char col1[] = "#212121";
static const char col2[] = "#1C1C1C";
static const char col3[] = "#696969";
static const char col0[] = "#C0C0C0";

static const char *colors[][3]      = {
	/*               fg    bg    border   */
	[SchemeNorm] = { col3, col2, col1},
	[SchemeSel]  = { col0, col1, col1},
};

static const unsigned int borderpx = 1; /* border pixel of windows   */
static const unsigned int gappx    = 2; /* gap pixel between windows */
static const unsigned int snap     = 8; /* snap pixel                */
static const Bool showbar          = 1; /* False means no bar        */
static const Bool topbar           = 1; /* False means bottom bar    */

/* tagging */
static const char *tags[] = {
  "\uE01E prod",
  "\uE01E dev",
  "\uE01E term",
  "\uE0B2 web",
  "\uE1EB media",
  "\uE0BE misc"
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium",  NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95]         */
static const int nmaster      = 1;    /* number of clients in master area                */
static const Bool resizehints = 0;    /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  {"\uE005" , tile}    , 
  {"\uE011" , NULL}    , 
  {"[M]"    , monocle} , 
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col3, "-nf", col1, "-sb", col2, "-sf", col3, NULL };
static const char *termcmd[]  = { "uxterm", NULL };
static const char *browser[]  = { "chromium", NULL, "Chromium"};

static Key keys[] = {
  /* modifier               key        function        argument */
  {MODKEY                 , XK_p                     , spawn          , {.v = dmenucmd}}                                             ,
  {MODKEY                 , XK_g                     , spawn          , {.v = browser}}                                              ,
  {MODKEY | ControlMask   , XK_g                     , spawn          , SHCMD ("chromium --proxy-server='socks5://localhost:9000'")} ,
  {MODKEY                 , XK_Escape                , spawn          , SHCMD ("xscreensaver-command -lock")}                        ,
  {MODKEY | ShiftMask     , XK_Return                , spawn          , {.v = termcmd}}                                              ,
  {0                      , 0x1008ff02               , spawn          , SHCMD ("xbacklight -inc 10")}                                ,
  {0                      , 0x1008ff03               , spawn          , SHCMD ("xbacklight -dec 10")}                                ,
  {0                      , 0x1008ff11               , spawn          , SHCMD ("amixer -c 1 set Master 1dB- unmute")}                ,
  {0                      , 0x1008ff12               , spawn          , SHCMD ("amixer -c 1 set Master mute")}                       ,
  {0                      , 0x1008ff13               , spawn          , SHCMD ("amixer -c 1 set Master 1dB+ unmute")}                ,
  {0                      , 0x1008ff59               , spawn          , SHCMD ("$HOME/.xrandr-toggle")}                              ,
  {MODKEY                 , XK_b                     , togglebar      , {0}}                                                         ,
  {MODKEY                 , XK_Right                 , focusstack     , {.i = +1}}                                                   ,
  {MODKEY                 , XK_Left                  , focusstack     , {.i = -1}}                                                   ,
  {MODKEY                 , XK_i                     , incnmaster     , {.i = +1}}                                                   ,
  {MODKEY                 , XK_d                     , incnmaster     , {.i = -1}}                                                   ,
  //{MODKEY | ControlMask , XK_j                     , pushdown       , {0}}                                                         ,
  //{MODKEY | ControlMask , XK_k                     , pushup         , {0}}                                                         ,
  {MODKEY | ShiftMask     , XK_j                     , movestack      , {.i = +1}}                                                   ,
  {MODKEY | ShiftMask     , XK_k                     , movestack      , {.i = -1}}                                                   ,
  {MODKEY | ShiftMask     , XK_Left                  , setmfact       , {.f = -0.05}}                                                ,
  {MODKEY | ShiftMask     , XK_Right                 , setmfact       , {.f = +0.05}}                                                ,
  {MODKEY                 , XK_Return                , spawn          , {.v = termcmd}}                                              ,
  {MODKEY                 , XK_Tab                   , view           , {0}}                                                         ,
  {MODKEY | ShiftMask     , XK_c                     , killclient     , {0}}                                                         ,
  {MODKEY                 , XK_t                     , setlayout      , {.v = &layouts[0]}}                                          ,
  {MODKEY                 , XK_f                     , setlayout      , {.v = &layouts[1]}}                                          ,
  {MODKEY                 , XK_m                     , setlayout      , {.v = &layouts[2]}}                                          ,
  {MODKEY                 , XK_space                 , setlayout      , {0}}                                                         ,
  {MODKEY | ShiftMask     , XK_space                 , togglefloating , {0}}                                                         ,
  {MODKEY                 , XK_0                     , view           , {.ui = ~0}}                                                  ,
  {MODKEY | ShiftMask     , XK_0                     , tag            , {.ui = ~0}}                                                  ,
  {MODKEY                 , XK_comma                 , focusmon       , {.i = -1}}                                                   ,
  {MODKEY                 , XK_period                , focusmon       , {.i = +1}}                                                   ,
  {MODKEY | ShiftMask     , XK_comma                 , tagmon         , {.i = -1}}                                                   ,
  {MODKEY | ShiftMask     , XK_period                , tagmon         , {.i = +1}}                                                   ,
  TAGKEYS (XK_1, 0)
  TAGKEYS (XK_2, 1)
  TAGKEYS (XK_3, 2)
  TAGKEYS (XK_4, 3)
  TAGKEYS (XK_5, 4)
  TAGKEYS (XK_6, 5)
  TAGKEYS (XK_7, 6)
  TAGKEYS (XK_8, 7)
  TAGKEYS (XK_9, 8) {MODKEY | ControlMask , XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

