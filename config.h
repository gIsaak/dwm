/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static unsigned int borderpx             = 2;        /* border pixel of windows */
static unsigned int snap                 = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;     /* 0 means no systray */
static int swallowfloating               = 0;        /* 1 means swallow floating windows by default */
static unsigned int gappih               = 10;       /* horiz inner gap between windows */
static unsigned int gappiv               = 10;       /* vert inner gap between windows */
static unsigned int gappoh               = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov               = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps                     = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int ulinepad       = 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	 = 2;	/* height of the underline */
static const unsigned int ulinevoffset	 = 0;	/* vertical offset from bottom of bar */
static const int unline 		         = 1;	/* 1 to show underline , 0 for the normal square */
static int showbar                       = 1;        /* 0 means no bar */
static int topbar                        = 1;        /* 0 means bottom bar */
static const char *fonts[]               = { "HackNerdFont:size=10",
                                             "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"};

static const char dmenufont[]            = "HackNerdFont:size=10";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#444444";
static char normfgcolor[]                = "#bbbbbb";
static char selfgcolor[]                 = "#eeeeee";
static char selbordercolor[]             = "#005577";
static char selbgcolor[]                 = "#005577";
static char warnfgcolor[]                = "#ffff00";
static char warnbgcolor[]                = "#000000";
static char warnbordercolor[]            = "#000000";
static char urgentfgcolor[]              = "#ff0000";
static char urgentbgcolor[]              = "#000000";
static char urgentbordercolor[]          = "#000000";
static const unsigned int baralpha       = 0xFF;
static const unsigned int borderalpha    = OPAQUE;

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm]   = { normfgcolor,   normbgcolor,   normbordercolor },
       [SchemeSel]    = { selfgcolor,    selbgcolor,    selbordercolor  },
       [SchemeWarn]   =	{ warnfgcolor,   warnbgcolor,   warnbordercolor },
       [SchemeUrgent] =	{ urgentfgcolor, urgentbgcolor, urgentbordercolor },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm]    = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]     = { OPAQUE, baralpha, borderalpha },
    [SchemeWarn]    = { OPAQUE, baralpha, borderalpha },
    [SchemeUrgent]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                 instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",                NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Brave-browser",       NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{  TERMCLASS,            NULL,     NULL,           0,         0,          1,           0,        -1 },
    { "zoom",                NULL,     NULL,           1 << 7,    0,          0,          -1,        -1 },
	{ "Matplotlib",          NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ "Julia",               NULL,     NULL,           0,         1,          0,           1,        -1 },
	{  NULL,                 NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", normfgcolor, "-sf", normbgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color4",             STRING,  &normfgcolor },
		{ "color0",             STRING,  &normbgcolor },
		{ "color8",             STRING,  &normbordercolor },
		{ "color15",            STRING,  &selfgcolor },
		{ "color0",             STRING,  &selbgcolor },
		{ "color15",            STRING,  &selbordercolor },
        // { "color5",             STRING,  &warnfgcolor},
        { "color0",             STRING,  &warnbgcolor},
        { "color0",             STRING,  &warnbordercolor },
        // { "color6",             STRING,  &urgentfgcolor},
        { "color0",             STRING,  &urgentbgcolor},
        { "color0",             STRING,  &urgentbordercolor },
		{ "borderpx",          	INTEGER, &borderpx },
        { "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,			            XK_z,	   incrgaps,	   {.i = +3 } },
	{ MODKEY,			            XK_x,	   incrgaps,	   {.i = -3 } },
	{ MODKEY,			            XK_a,	   togglegaps,	   {0} },
	{ MODKEY|ShiftMask,		        XK_a,      defaultgaps,	   {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ControlMask,           XK_w,      spawn,          SHCMD("$BROWSER_INCOGNITO") },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
    { 0, XF86XK_AudioMute,          spawn,      SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioRaiseVolume,   spawn,      SHCMD("pamixer -i 2; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioLowerVolume,   spawn,      SHCMD("pamixer -d 2; kill -44 $(pidof dwmblocks)") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

