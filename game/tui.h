#ifndef TUI_H_
#define TUI_H_
#include "view.h"

class Tui : public View
{
	private:
		int col, row;	
		Tui();
	public:
		static Tui* get()
		{
			static Tui singleData;
			return &singleData;
		}
		~Tui();
		void clear();
		void draw ();
		void run  ();
		void winx ();
		void winy ();
};

#endif //TUI_H_
