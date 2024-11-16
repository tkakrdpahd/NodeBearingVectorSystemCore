#include "Menu.h"
#include "SocketManager.h"
#include <memory>

// 전역 스마트 포인터 선언 (외부에서 접근)
extern std::shared_ptr<SocketManager> g_socketManager;

void menu(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io, int& counter, float& f) {
    if (ImGui::Begin("Server Control")) {
        // Start Server 버튼
        if (ImGui::Button("Start Server")) {
            if (g_socketManager && g_socketManager->StartServer()) {
                ImGui::Text("Server started successfully on port %d", g_socketManager->getPort());
            } else {
                ImGui::Text("Failed to start the server.");
            }
        }

        // Stop Server 버튼
        if (ImGui::Button("Stop Server")) {
            if (g_socketManager) {
                g_socketManager->closeServer();
                ImGui::Text("Server stopped.");
            }
        }
    }
    ImGui::End();
}
