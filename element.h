#ifndef ELEMENT_H_INC
#define ELEMENT_H_INC

typedef unsigned char element;

static inline bool is_empty(element e) {
	return e == (unsigned char)-1;
}

static inline void set_empty(element& e) {
	e = (unsigned char)-1;
}

static inline char get_char(element e) {
	static char c[] = {'o', 'x', '*', '#', '=', 'l', '-', '+'};
	if (e == (unsigned char)-1) {
		return ' ';
	}
	else {
		return c[e];
	}
}

#endif
