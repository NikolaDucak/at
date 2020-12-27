#ifndef __AT_TUI_H__
#define __AT_TUI_H__

#include <ncurses.h>
#include <string>

/**
 * A wrapper around ncurses lib functionality for more readable names 
 * & some additional features such as std::string for const char * arguments.
 */
namespace tui
{
	using uint = unsigned int;

	struct point{ int x, y; };

	void  init_terminal();
	void  end_terminal();
	point term_size();

	int  input();
	void render();
	void clear();

	std::string cursor_at(uint x, uint y);
	void print_at(uint x, uint y, const std::string& str);
}

#endif
