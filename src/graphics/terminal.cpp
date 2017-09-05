#include <graphics/terminal.h>
#include <string>

using namespace std;

terminal::terminal(int x, int y, int width, int height) : 
                   window (x, y, width, height){
    this -> history;
}

terminal::~terminal(){

}

void terminal::update(){
    wattron(box_window, COLOR_PAIR(colorPair));
    box(box_window, 0, 0);
    wattroff(box_window, COLOR_PAIR(colorPair));
    int index = history.size() > height - 3 ? history.size() - height + 3 : 0;
    int start_y = index != 0 ? 0 : height - history.size() - 3;
    for (int i = index; i < history.size(); i++){
        mvwprintw(_window, start_y + i - index, 0, history[i].c_str());
    }
    mvwprintw(_window, 0, width - 10, "%d", history.size());
    wmove(_window, height - 3, 0);
    wrefresh(box_window);
    wrefresh(_window);
}

int terminal::run(){
    char c[150];
    bool cont = true;
    update();
    while(cont){
        wgetstr(_window, c);
        this -> str = string(c);
        this -> history.push_back(str);
        if (history.size() > 100){
            history.erase(history.begin());
        }
        update();
    }
    return 0;
}
