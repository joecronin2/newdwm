/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 13;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* Minimal heigt of a client for smfact */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] 					= { "0xProto Nerd Font:size=10" };
/*static const char *fonts[]          = { "monospace:size=10" };*/
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
static const char *tags[] = { "=", "(", "{", "*", ">", ";", ",", ".", "p", "y" };

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
static const float smfact     = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "%",      	tile2 },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  &((Keychord){1, {{ControlMask, KEY}}, view,{.ui = 1 << TAG} }), \
  &((Keychord){1, {{MODKEY|ShiftMask, KEY}}, toggleview,     {.ui = 1 << TAG} }), \
  &((Keychord){1, {{MODKEY|ControlMask, KEY}}, tag,     {.ui = 1 << TAG} }), \
  &((Keychord){1, {{SUPERKEY|ControlMask, KEY}}, toggletag,     {.ui = 1 << TAG} }), \

/*#define TAGKEYS(KEY,TAG)                                                                                               \*/
/*       &((Keychord){1, {{MODKEY, KEY}},                              view,           {.ui = 1 << TAG} }), \*/
/*       &((Keychord){1, {{MODKEY|ControlMask, KEY}},                   toggleview,     {.ui = 1 << TAG} }), \*/
/*       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                       tag,            {.ui = 1 << TAG} }), \*/
/*       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},         toggletag,      {.ui = 1 << TAG} }),*/
/**/
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *rofi_cmd[] = { "rofi", "-show", "drun" };
static const char *browser_cmd[] = { "librewolf", NULL };
  
/*static const Key keys[] = {*/
static Keychord *keychords[] = {
	/* modifier                     key        function        argument */
	/*{ SUPERKEY,                     XK_k,      spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-") },*/
	/*{ SUPERKEY,                     XK_j,      spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+") },*/
	&((Keychord){1, {{ SUPERKEY,                     XK_k}},      spawn,          SHCMD("pactl set-sink-volume alsa_output.usb-Focusrite_Scarlett_Solo_USB_Y79Y5F416098C2-00.HiFi__Line1__sink -5%") }),
	&((Keychord){1, {{ SUPERKEY,                     XK_j}},      spawn,          SHCMD("pactl set-sink-volume alsa_output.usb-Focusrite_Scarlett_Solo_USB_Y79Y5F416098C2-00.HiFi__Line1__sink +5%") }),
	&((Keychord){1, {{ MODKEY, XK_q}}, spawn, SHCMD ("rofi -show calc -modi calc -no-show-match -no-sort") }),
	&((Keychord){1, {{ ControlMask,           				XK_i}},      spawn,          { .v = browser_cmd } }),
	&((Keychord){1, {{ MODKEY,                       XK_minus}},  setgaps,        {.i = -1 } }),
	&((Keychord){1, {{ MODKEY,                       XK_equal}},  setgaps,        {.i = +1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_equal}},  setgaps,        {.i = 0  } }),
	&((Keychord){1, {{ MODKEY|ShiftMask|ControlMask, XK_t}},      trippy,         { 0 } }),
	&((Keychord){1, {{ MODKEY|ControlMask, 					XK_o}},      adjust_temperature,       {.i = 50 } }),
	&((Keychord){1, {{ MODKEY|ControlMask, 					XK_a}}, 		 adjust_temperature, { .i = -(50) } }),
  &((Keychord){1, {{ MODKEY|ControlMask|ShiftMask, XK_o}}, 		 adjust_brightness, { .i = 3 } }),
  &((Keychord){1, {{ MODKEY|ControlMask|ShiftMask, XK_a}}, 		 adjust_brightness, { .i = -(3) } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_h}},      setsmfact,      {.f = +0.05} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_l}},      setsmfact,      {.f = -0.05} }),
	&((Keychord){1, {{ MODKEY,                       XK_p}},      spawn,          {.v = rofi_cmd } }),
	&((Keychord){1, {{ ControlMask,								 	XK_dollar}}, spawn,          {.v = termcmd } }),
	&((Keychord){1, {{ MODKEY,                       XK_b}},      togglebar,      {0} }),
	&((Keychord){1, {{ MODKEY,                       XK_h}},      focusstack,     {.i = +1 } }),
	&((Keychord){1, {{ MODKEY,                       XK_u}},      focusstack,     {.i = -1 } }),
	&((Keychord){1, {{ MODKEY,                       XK_e}},      incnmaster,     {.i = +1 } }),
	&((Keychord){1, {{ MODKEY,                       XK_t}},      incnmaster,     {.i = -1 } }),
	&((Keychord){1, {{ MODKEY,                       XK_semicolon}},setmfact,     {.f = -0.05} }),
	&((Keychord){1, {{ MODKEY,                       XK_l}},      setmfact,       {.f = +0.05} }),
	&((Keychord){1, {{ MODKEY,                       XK_Return}}, zoom,           {0} }),
	&((Keychord){1, {{ MODKEY,                       XK_Tab}},    view,           {0} }),
	&((Keychord){1, {{ ControlMask,                  XK_j}},      killclient,     {0} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_t}},      setlayout,      {.v = &layouts[0]} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_f}},      setlayout,      {.v = &layouts[1]} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_m}},      setlayout,      {.v = &layouts[2]} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_n}},      setlayout,      {.v = &layouts[3]} }),
	&((Keychord){1, {{ MODKEY,                       XK_space}},  setlayout,      {0} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_space}},  togglefloating, {0} }),
	&((Keychord){1, {{ MODKEY,                       XK_g}},      view,           {.ui = ~0 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_g}},      tag,            {.ui = ~0 } }),
	&((Keychord){1, {{ MODKEY,                       XK_comma}},  focusmon,       {.i = -1 } }),
	&((Keychord){1, {{ MODKEY,                       XK_period}}, focusmon,       {.i = +1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_comma}},  tagmon,         {.i = -1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,             XK_period}}, tagmon,         {.i = +1 } }),
  &((Keychord){1, {{MODKEY|ShiftMask, XK_q}},                             quit,           {0} }),
	TAGKEYS(                        XK_equal,                  0)
	TAGKEYS(                        XK_parenleft,              1)
	TAGKEYS(                        XK_braceleft,              2)
	TAGKEYS(                        XK_asterisk,               3)
	TAGKEYS(                        XK_greater,                4)
	TAGKEYS(                        XK_semicolon,              5)
	TAGKEYS(                        XK_comma,                  6)
	TAGKEYS(                        XK_period,                 7)
	TAGKEYS(                        XK_p,                      8)
	TAGKEYS(                        XK_y,                      9)
	/*{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },*/
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

