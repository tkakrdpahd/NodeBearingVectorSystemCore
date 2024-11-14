/**
 * Menu.h
 * 
 * Purpose:
 * Create Main Menu GUI
 */

#ifndef MENU_H
#define MENU_H

#include <imgui.h>

// 필요한 변수들을 매개변수로 전달
void menu(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io, int& counter, float& f);

#endif // MENU_H
