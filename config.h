/* See LICENSE file for copyright and license details. */

/* appearance */

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 22;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "noto sans mono:size=9" };
static const char dmenufont[]       = "noto sans mono:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]	    = "#000000"; /*black*/
static const char col_white[]	    = "#ffffff"; /*white*/
static const char col_midblue[]     = "#000033"; /*midnight blue*/
static const char col_royal[]       = "#000066"; /*royal blue*/
static const char col_icy[]	    = "#98d8ea"; /*icy blue*/
static const char *colors[][3]      = {
	/*               fg (fonts)  bg (bars)   border   */
	[SchemeNorm] = { col_gray3, col_black, col_gray1 }, /* unselected */
	[SchemeSel]  = { col_gray4, col_midblue, col_icy }, /*selected*/
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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

/* commands */
/* nb is normal background, sb is selected background, nf is normal font, sf is selected font */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_gray3, "-sb", col_midblue, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/* Custom Programs */
static const char *roficmd[] = {"rofi", "-show", "run"};
static const char *screenlock[] = {"lock", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, 	/* Opens dmenu */
	{ MODKEY,            		XK_Return, spawn,          {.v = termcmd } }, 	/* Opens a Terminal */
	{ MODKEY,		        XK_m,	   spawn,          {.v = roficmd } }, 	/* Opens Rofi */
	{ MODKEY|ControlMask,		XK_l,	   spawn,          {.v = screenlock} }, /* Locks Screen */
	{ MODKEY,                       XK_b,      togglebar,      {0} }, 		/* Toggles the TOP BAR on/off */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, 	/* Move down in the stack */
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } }, 	/* Move up in the stack */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },        /* Increment FORWARD through layout styles */
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },	/* Decrement BACKWARDS through layout style */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, 	/* Minimizes the size of the master */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, 	/* Increases the size of the master */
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} }, 		/* Move back to previous workspace */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} }, 		/* Closes the focused window */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },/* TILING LAYOUT */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },/* FLOATING LAYOUT */
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[2]} },/* GRAND/MONACLE LAYOUT */
	{ MODKEY,                       XK_space,  setlayout,      {0} }, 		/*Switches between tiling and monacle, or tiling and floating*/
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} }, 		/* This will float the highlighted/focused window within the workspace*/
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, 	/* VIEW ALL WINDOWS ON SAME WORKSPACE */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, 	/* PLACES ACTIVE WINDOW ON EVERY WORKSPACE */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0) 			/****** SWITCHES DESKTOPS BY NUMBER *******/
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },		 /********** EXITS DWM SESSION **********/
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

