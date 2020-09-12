/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /*gap pixel between windows */
static const unsigned int snap      = 22;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Noto Sans SemiBold:size=8" };
static const char dmenufont[]       = "Noto Sans SemiBold:size=8";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#888888";
static const char col_gray4[]       = "#cccccc";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000"; /*black*/
static const char col_white[]       = "#ffffff"; /*white*/
static const char col_midblue[]     = "#000022"; /*midnight blue*/
static const char col_royal[]       = "#000066"; /*royal blue*/
static const char col_icy[]         = "#98d8ea"; /*icy blue*/

static const unsigned int baralpha = 0xAA;
static const unsigned int borderalpha = 0xcc;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_black, col_gray1 },
	[SchemeSel]  = { col_white, col_midblue,  col_icy  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
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
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

# include "fibonacci.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
        { "[@]",      spiral },
        { "[\\]",      dwindle },

};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT    Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_gray3, "-sb", col_midblue, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "termite", NULL };

/* Custom Programs */
static const char *roficmd[] = {"rofi", "-show", "run"};
static const char *rofishow[] = {"rofi", "-show", "window"};
static const char *screenlock[] = {"lock", NULL };
static const char *volumeup[]= {"pulseaudio-ctl", "up"};
static const char *volumedown[]= {"pulseaudio-ctl", "down"};
static const char *volumemute[]= {"pulseaudio-ctl", "mute"};

static const char *brightnessup[]= {"light", "-A", "5","-O", NULL};
static const char *brightnessdown[]= {"light", "-U", "5", "-O", NULL};

static const char *ranger[]= {"termite", "ranger",NULL};
static const char *browser[]= {"brave", NULL};
static const char *mt4[]= {"mt4", NULL};
static const char *mt4edit[]= {"mt4editor", NULL};
static const char *thunar[]= {"thunar", NULL};
static const char *screenshot[]= {"scrot", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, 	/* Opens dmenu */
	{ MODKEY,            		XK_Return, spawn,          {.v = termcmd } }, 	/* Opens a Terminal */
	{ MODKEY,		        XK_m,	   spawn,          {.v = roficmd } }, 	/* Opens Rofi Search*/
	{ MODKEY,		        XK_n,	   spawn,          {.v = rofishow } }, 	/* Rofi Open Window Search*/
	{ MODKEY|ControlMask,		XK_l,	   spawn,          {.v = screenlock} }, /* Locks Screen */
	{ MODKEY,                       XK_Prior,  spawn,          {.v = volumeup } }, 	/* Volume Up */
	{ MODKEY,            		XK_Next,   spawn,          {.v = volumedown } }, 	/* Volume Down */
	{ MODKEY,		        XK_End,	   spawn,          {.v = volumemute } }, 	/* Mute */
	
	{ MODKEY,            		XK_F10,    spawn,          {.v = brightnessup} }, 	/* Screen Brightness Up */
	{ MODKEY,		        XK_F9,	   spawn,          {.v = brightnessdown} }, 	/* Screen Brightness Down */

	{ MODKEY|ALT,          		XK_b, 	   spawn,          {.v = browser } }, 	/* Opens Web Browser */
	{ MODKEY|ALT,		        XK_m,	   spawn,          {.v = mt4  } }, 		/* Opens MT4 */
	{ MODKEY|ALT,		        XK_e,	   spawn,          {.v = mt4edit  } }, 		/* Opens MT4 MetaEditor */

	{ MODKEY|ALT,			XK_r,	   spawn,          {.v = ranger} }, 	/* Opens Ranger in st */
	{ MODKEY|ALT,			XK_t,	   spawn,          {.v = thunar} }, 	/* Opens GUI File Manager */
	{ MODKEY,			XK_Insert, spawn,          {.v = screenshot} }, 	/* Takes a Screenshot */

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
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },/* Fibonacci Spiral Layout */
        { MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },/* Dwindle Layout */


	{ MODKEY,                       XK_space,  setlayout,      {0} }, 		/*Switches between tiling and monacle, or tiling and floating*/
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} }, 		/* This will float the highlighted/focused window within the workspace*/
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, 	/* VIEW ALL WINDOWS ON SAME WORKSPACE */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, 	/* PLACES ACTIVE WINDOW ON EVERY WORKSPACE */

	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

         { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
         { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
         { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },



	TAGKEYS(                        XK_1,                      0) 			/****** SWITCHES DESKTOPS BY NUMBER *******/
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
/*	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },	*/	 /********** EXITS DWM SESSION **********/

	{ MODKEY|ShiftMask,             XK_F12,      quit,           {0} },		 /********** EXITS DWM SESSION **********/
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

