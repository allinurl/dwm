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
	{ "Chromium"         ,  NULL,       NULL,       1 << 3,       0,           -1 },
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

#define KEYEVENT(SRC_MOD,SRC_KEY,DST_MOD,DST_KEY) \
	{ SRC_MOD, SRC_KEY, sendkeyevent, { .v = &(const KeyBinding){ DST_MOD, DST_KEY } } },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *browser[]     = { "chromium", NULL, "Chromium"};
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col3, "-nf", col1, "-sb", col2, "-sf", col3, NULL };
static const char *termcmd[]     = { "xterm", "-fa", "Terminus", "-fs", "9", "-u8", NULL };

static Key keys[] = {
  /* modifier               key        function        argument */
  {MODKEY               , XK_p       , spawn          , {.v = dmenucmd}},
  {MODKEY | ControlMask , XK_g       , spawn          , SHCMD ("chromium --proxy-server='socks5://localhost:9000' --proxy-bypass-list='<-loopback>'")},
  {MODKEY | ShiftMask   , XK_g       , spawn          , SHCMD ("chromium --user-data-dir=$HOME/.config/chromium/local --incognito")},
  {MODKEY               , XK_g       , spawn          , {.v = browser}},
  {MODKEY               , XK_Escape  , spawn          , SHCMD("sh -c 'xlock -mode blank & sleep 1; xset dpms force off'") },
  {MODKEY | ShiftMask   , XK_Return  , spawn          , SHCMD("tabbed -c xterm -fa Terminus -fs 9 -u8 -into") },
  {0                    , 0x1008ff02 , spawn          , SHCMD ("brightnessctl set +10%")},
  {0                    , 0x1008ff03 , spawn          , SHCMD ("brightnessctl set 10%-")},
  {0                    , 0x1008ff11 , spawn          , SHCMD("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%-") },
  {0                    , 0x1008ff12 , spawn          , SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
  {0                    , 0x1008ff13 , spawn          , SHCMD("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%+") },
  {0                    , 0x1008ff59 , spawn          , SHCMD ("$HOME/.xrandr-toggle")},
  {MODKEY               , XK_b       , togglebar      , {0}},
  {MODKEY               , XK_Right   , focusstack     , {.i = +1}},
  {MODKEY               , XK_Left    , focusstack     , {.i = -1}},
  {MODKEY               , XK_i       , incnmaster     , {.i = +1}},
  {MODKEY               , XK_d       , incnmaster     , {.i = -1}},
  {MODKEY | ShiftMask   , XK_j       , movestack      , {.i = +1}},
  {MODKEY | ShiftMask   , XK_k       , movestack      , {.i = -1}},
  {MODKEY | ShiftMask   , XK_Left    , setmfact       , {.f = -0.05}},
  {MODKEY | ShiftMask   , XK_Right   , setmfact       , {.f = +0.05}},
  {MODKEY               , XK_Return  , spawn          , {.v = termcmd}},
  {MODKEY               , XK_Tab     , view           , {0}},
  {MODKEY | ShiftMask   , XK_c       , killclient     , {0}},
  {MODKEY               , XK_t       , setlayout      , {.v = &layouts[0]}},
  {MODKEY               , XK_f       , setlayout      , {.v = &layouts[1]}},
  {MODKEY               , XK_m       , setlayout      , {.v = &layouts[2]}},
  {MODKEY               , XK_space   , setlayout      , {0}},
  {MODKEY | ShiftMask   , XK_space   , togglefloating , {0}},
  {MODKEY               , XK_0       , view           , {.ui = ~0}},
  {MODKEY | ShiftMask   , XK_0       , tag            , {.ui = ~0}},
  {MODKEY               , XK_comma   , focusmon       , {.i = -1}},
  {MODKEY               , XK_period  , focusmon       , {.i = +1}},
  {MODKEY | ShiftMask   , XK_comma   , tagmon         , {.i = -1}},
  {MODKEY | ShiftMask   , XK_period  , tagmon         , {.i = +1}},

	// Navigation(two-handed)
	KEYEVENT(Mod1Mask, XK_h, 0, XK_Left)
	KEYEVENT(Mod1Mask, XK_l, 0, XK_Right)
	KEYEVENT(Mod1Mask, XK_k, 0, XK_Up)
	KEYEVENT(Mod1Mask, XK_j, 0, XK_Down)
	KEYEVENT(Mod1Mask, XK_p, 0, XK_Up)
	KEYEVENT(Mod1Mask, XK_n, 0, XK_Down)
	KEYEVENT(Mod1Mask, XK_i, ControlMask, XK_Left)
	KEYEVENT(Mod1Mask, XK_o, ControlMask, XK_Right)
	KEYEVENT(Mod1Mask, XK_equal, ControlMask, XK_Home)
	KEYEVENT(Mod1Mask, XK_minus, ControlMask, XK_End)
	// Navigation(one-handed)
	KEYEVENT(Mod1Mask, XK_s, 0, XK_Up)
	KEYEVENT(Mod1Mask, XK_x, 0, XK_Down)
	KEYEVENT(Mod1Mask, XK_z, 0, XK_Left)
	KEYEVENT(Mod1Mask, XK_c, 0, XK_Right)
	KEYEVENT(Mod1Mask, XK_d, 0, XK_Return)
	KEYEVENT(Mod1Mask, XK_a, 0, XK_Home)
	KEYEVENT(Mod1Mask, XK_e, 0, XK_End)
	// Selection(two-handed)
	KEYEVENT(Mod1Mask|ShiftMask, XK_h, ShiftMask, XK_Left)
	KEYEVENT(Mod1Mask|ShiftMask, XK_l, ShiftMask, XK_Right)
	KEYEVENT(Mod1Mask|ShiftMask, XK_k, ShiftMask, XK_Up)
	KEYEVENT(Mod1Mask|ShiftMask, XK_j, ShiftMask, XK_Down)
	KEYEVENT(Mod1Mask|ShiftMask, XK_p, ShiftMask, XK_Up)
	KEYEVENT(Mod1Mask|ShiftMask, XK_n, ShiftMask, XK_Down)
	KEYEVENT(Mod1Mask|ShiftMask, XK_i, ControlMask|ShiftMask, XK_Left)
	KEYEVENT(Mod1Mask|ShiftMask, XK_o, ControlMask|ShiftMask, XK_Right)
	KEYEVENT(Mod1Mask|ShiftMask, XK_equal, ControlMask|ShiftMask, XK_Home)
	KEYEVENT(Mod1Mask|ShiftMask, XK_minus, ControlMask|ShiftMask, XK_End)
	// Selection(one-handed)
	KEYEVENT(Mod1Mask|ShiftMask, XK_s, ShiftMask, XK_Up)
	KEYEVENT(Mod1Mask|ShiftMask, XK_x, ShiftMask, XK_Down)
	KEYEVENT(Mod1Mask|ShiftMask, XK_z, ShiftMask, XK_Left)
	KEYEVENT(Mod1Mask|ShiftMask, XK_c, ShiftMask, XK_Right)
	KEYEVENT(Mod1Mask|ShiftMask, XK_a, ShiftMask, XK_Home)
	KEYEVENT(Mod1Mask|ShiftMask, XK_e, ShiftMask, XK_End)

  //{MODKEY | ControlMask , XK_j     , pushdown       , {0}},
  //{MODKEY | ControlMask , XK_k     , pushup         , {0}},
    // Custom remapping for Home and End keys
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
  /* click         eventmask button    function        argument */
  { ClkLtSymbol   , 0      , Button1 , setlayout      , {0} },
  { ClkLtSymbol   , 0      , Button3 , setlayout      , {.v = &layouts[2]} },
  { ClkWinTitle   , 0      , Button2 , zoom           , {0} },
  { ClkStatusText , 0      , Button2 , spawn          , {.v = termcmd } },
  { ClkClientWin  , MODKEY , Button1 , movemouse      , {0} },
  { ClkClientWin  , MODKEY , Button2 , togglefloating , {0} },
  { ClkClientWin  , MODKEY , Button3 , resizemouse    , {0} },
  { ClkTagBar     , 0      , Button1 , view           , {0} },
  { ClkTagBar     , 0      , Button3 , toggleview     , {0} },
  { ClkTagBar     , MODKEY , Button1 , tag            , {0} },
  { ClkTagBar     , MODKEY , Button3 , toggletag      , {0} },
};

