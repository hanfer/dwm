/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-20-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#3F4742";
static const char normbgcolor[]     = "#272822";
static const char normfgcolor[]     = "#F8F8F2";
static const char selbordercolor[]  = "#F8F8F2";
static const char selbgcolor[]      = "#595959";
static const char selfgcolor[]      = "#F8F8F2";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static char *tags[2][9] = {
	{ "main" , "files", "www", "code", "testing", "6",     "7",		"8",     "9" },
	{ "main" , "irc",   "www", "code", "testing", "music", "steam", "skype", "9" }
};

static const Rule rules[] = {
	/* class 			instance    		title           tags mask   isfloating   monitor */
	{ "sublime-text",	NULL,				NULL,			1 << 3,		False,		-1 },
	{ "Chromium",		NULL,				NULL,			1 << 2,     False,      -1 },
	{ "MPlayer",		NULL,				NULL,			0,		 	True,	    -1 },
	{ "mpv",			NULL,				NULL,			0,		 	True,	    -1 },
	{ "Skype",			NULL,				NULL,			1 << 7,		False,	     1 },
	{ "noggit",			NULL,				"Noggit", 		0,		 	True,	    -1 },
	{ NULL,				"irc",				NULL,			1 << 1,		False,		 1 },
	{ NULL,				"ranger",			NULL,			1 << 1,		False,		 2 },
	{ NULL,				"music",			NULL,			1 << 5,		False,		 1 },
	{ NULL,				NULL,				"Qt Creator", 	1 << 3,		False,	    -1 },
	{ NULL,				"code terminal",	NULL,			1 << 3,		False,      -1 }
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

static const char *playcmd[]  = {"ncmpcpp", "toggle", NULL};
static const char *nextcmd[]  = {"ncmpcpp", "next",   NULL};
static const char *prevcmd[]  = {"ncmpcpp", "prev",   NULL};
static const char *stopcmd[]  = {"ncmpcpp", "stop",   NULL};

static Key keys[] = {
	/* modifier                     key        				function        		argument */
	{ MODKEY,                       XK_p,					spawn,          		{.v = dmenucmd } },
	{ MODKEY,            			XK_Return,				spawn,          		{.v = termcmd } },
	{ 0,							XF86XK_AudioPlay,		spawn,   				{.v = playcmd } },
	{ 0,							XF86XK_AudioNext,		spawn,   				{.v = nextcmd } },
	{ 0,							XF86XK_AudioPrev,		spawn,   				{.v = prevcmd } },
	{ 0,							XF86XK_AudioStop,		spawn,   				{.v = stopcmd } },
	{ MODKEY,                       XK_b,      				togglebar,      		{0} },
	{ MODKEY,                       XK_j,      				focusstack,     		{.i = +1 } },
	{ MODKEY,                       XK_k,      				focusstack,     		{.i = -1 } },
	{ MODKEY,                       XK_i,      				incnmaster,     		{.i = +1 } },
	{ MODKEY,                       XK_d,      				incnmaster,     		{.i = -1 } },
	{ MODKEY,                       XK_h,      				setmfact,       		{.f = -0.05} },
	{ MODKEY,                       XK_l,      				setmfact,       		{.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, 				zoom,           		{0} },
	{ MODKEY|ShiftMask,             XK_c,      				killclient,     		{0} },
	{ MODKEY,                       XK_t,      				setlayout,      		{.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      				setlayout,      		{.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      				setlayout,      		{.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  				setlayout,      		{0} },
	{ MODKEY|ShiftMask,             XK_space,  				togglefloating, 		{0} },
	{ MODKEY,                       XK_0,      				view,           		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      				tag,            		{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  				focusmon,       		{.i = -1 } },
	{ MODKEY,                       XK_period, 				focusmon,       		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  				tagmon,         		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 				tagmon,         		{.i = +1 } },
	{ MODKEY,                   	XK_Left,   				cycle,          		{.i = -1 } },
	{ MODKEY,                   	XK_Right,  				cycle,          		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   				tagcycle,       		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  				tagcycle,       		{.i = +1 } },
	TAGKEYS(                        XK_1,      				                		0)
	TAGKEYS(                        XK_2,      				                		1)
	TAGKEYS(                        XK_3,      				                		2)
	TAGKEYS(                        XK_4,      				                		3)
	TAGKEYS(                        XK_5,      				                		4)
	TAGKEYS(                        XK_6,      				                		5)
	TAGKEYS(                        XK_7,      				                		6)
	TAGKEYS(                        XK_8,      				                		7)
	TAGKEYS(                        XK_9,      				                		8)
	{ MODKEY|ShiftMask,             XK_q,      				quit,           		{0} },
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

