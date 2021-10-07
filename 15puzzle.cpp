//
//  15puzzle.cpp
//  
//
//  Created by Sai teja Varanasi on 05/04/21.
//
#include <cstdlib>
#include <iostream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
using namespace std;
char *int2charstar (int v) {
 char *s = new char[sizeof(int)];
 sprintf(s,"%d",v);
 return s;
};
class new_Button:public Fl_Button{
    int x_cord;
    int y_cord;
    int num_on_plate;
    bool service;
public:
    new_Button(int ax_cord,int ay_cord,int anum_on_plate):Fl_Button(50*(ay_cord+1),50*(ax_cord+1),50,50,int2charstar(anum_on_plate)){
        x_cord=ax_cord;
        y_cord=ay_cord;
        num_on_plate=anum_on_plate;
        service=false;
        if(num_on_plate==25){
            this->label("");
        }
    }
    void ask_service(){
        service=true;
    }
    void shut_service_request(){
        service=false;
    }
    void modify_button(int x){
        num_on_plate=x;
        if(x!=25){
            this->label(int2charstar(x));
        }
        else if(x==25){
            this->label("");
        }
    }
    int get_num_on_plate(){
        return num_on_plate;
    }
    bool is_clicked(){
        return service;
    }
};
class game_window:public Fl_Window{
    new_Button *a[5][5];
    int x;
    int y;
public:
    game_window():Fl_Window(600,600,"puzzle"){
        x=4;
        y=4;
        back=new Fl_Button(500,500,30,30,"back");
        init_buttons();
    }
    void init_buttons(){
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                 a[i][j]=new new_Button(i,j,5*i+j+1);
            }
        }
    }
    bool is_neighbour(int i,int j){
        return abs(i-x)+abs(j-y)==1;
    }
    int handle(int v){
        if(v==FL_PUSH){
            double x_push=Fl::event_x();
            double y_push=Fl::event_y();
            for(int i=0;i<5;i++){
                for(int j=0;j<5;j++){
                    if(50*(j+1)<=x_push&&x_push<50*(j+2)&&50*(i+1)<=y_push&&y_push<50*(i+2)){
                        a[i][j]->ask_service();
                    }
                    if(a[i][j]->is_clicked()){
                        if(is_neighbour(i,j)){
                            a[x][y]->modify_button(a[i][j]->get_num_on_plate());
                            a[i][j]->modify_button(25);
                            x=i;
                            y=j;
                        }
                        a[i][j]->shut_service_request();
                    }
                }
            }
        }
    }
};
int main(){
    game_window* win=new game_window();
    win->show();
    return Fl::run();
}


