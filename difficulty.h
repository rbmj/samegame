#ifndef DIFFICULTY_H_INC
#define DIFFICULTY_H_INC

struct difficulty {
	const char * tag;
	unsigned numcols;
	unsigned numrows;
	unsigned numcolors;
};

const difficulty levels[] = {
	{
		"Army (super easy)",
		8,
		8,
		3
	},
	{
		"Air Force (pretty slack)",
		14,
		10,
		4
	},
	{
		"Coast Guard (almost a challenge)",
		16,
		14,
		6
	},
	{
		"Navy/Marine (a real test of your skills)",
		26,
		28,
		8
	}
};

#endif
