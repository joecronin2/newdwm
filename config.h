/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 13;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] 					= { "0xProto Nerd Font:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "a", "o", "e", "i", "u", "d", "h", "t", "n", "s", };

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
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *rofi_cmd[] = { "rofi", "-show", "drun" };
static const char *browser_cmd[] = { "librewolf", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                     	XK_k,      spawn,          SHCMD("pactl set-sink-volume alsa_output.usb-Focusrite_Scarlett_Solo_USB_Y79Y5F416098C2-00.HiFi__Line1__sink -5%") },
	{ MODKEY,                     	XK_comma,  spawn,          SHCMD("pactl set-sink-volume alsa_output.usb-Focusrite_Scarlett_Solo_USB_Y79Y5F416098C2-00.HiFi__Line1__sink +5%") },
	{ MODKEY, 											XK_q,		 	 spawn, SHCMD ("rofi -show calc -modi calc -no-show-match -no-sort | xclip -selection clipboard") },
	{ ControlMask,									XK_grave,  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = rofi_cmd } },
	{ ControlMask,                  XK_u,      spawn,          {.v = browser_cmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_comma,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_r,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_period, incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_g,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_semicolon,setmfact,     {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_w,			 zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,					              XK_c,      killclient,     {0} },
	// { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	// { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_a,                      0)
	TAGKEYS(                        XK_o,                      1)
	TAGKEYS(                        XK_e,                      2)
	TAGKEYS(                        XK_i,                      3)
	TAGKEYS(                        XK_u,                      4)
	TAGKEYS(                        XK_d,                      5)
	TAGKEYS(                        XK_h,                      6)
	TAGKEYS(                        XK_t,                      7)
	TAGKEYS(                        XK_n,                      8)
	TAGKEYS(                        XK_s,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ SUPERKEY, 										XK_e,      adjust_temperature,       {.i = 50 } },
	{ SUPERKEY, 										XK_o, 		 adjust_temperature, { .i = -(50) } },
	{ SUPERKEY|ShiftMask, 					XK_e, 		 adjust_brightness, { .i = 3 } },
	{ SUPERKEY|ShiftMask, 					XK_o, 		 adjust_brightness, { .i = -(3) } },

	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

