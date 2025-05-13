//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"", "free --mebi | awk '/^Mem/ { print $3 }' ",	3,		0},
	{"", "~/scripts/get_weather.sh",	3600,		0},
	{"", "cat /proc/loadavg | cut -d' ' -f1,2,3",	1,		0},

	{"", "date '+%b %d (%a) %I:%M%p'",					5,		0},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
