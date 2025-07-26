#include <imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <imgui_node_editor.h> // Use imgui-node-editor

namespace ed = ax::NodeEditor;

int main() {
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui Example", NULL, NULL);
    if (!window)
        return -1;

    glfwMakeContextCurrent(window);
    glewInit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Setup NodeEditor context
    ed::Config config;
    ed::EditorContext* editorContext = ed::CreateEditor(&config);

    // Example node/link state
    static ed::NodeId node_id_1 = 1;
    static ed::NodeId node_id_2 = 2;
    static ed::PinId input_id = 3;
    static ed::PinId output_id = 4;
    static ed::LinkId link_id = 5;
    static bool link_created = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- Main Fullscreen Window ---
        // This window acts as the "docking space" container.
        // All UI panels are implemented as child windows inside this main window.
        // The main window fills the entire viewport.
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        // Window flags:
        // - No title bar, no collapse, no move, no bring-to-front, no nav focus.
        // - Resizable is ENABLED (no ImGuiWindowFlags_NoResize).
        //   This allows the user to resize the main window if the OS window is resized.
        ImGuiWindowFlags main_window_flags = //ImGuiWindowFlags_NoTitleBar |
                                             ImGuiWindowFlags_NoMove |
                                             ImGuiWindowFlags_NoCollapse |
                                             ImGuiWindowFlags_NoBringToFrontOnFocus |
                                             ImGuiWindowFlags_NoNavFocus;
        ImGui::Begin("MainWindow", nullptr, main_window_flags);

        // --- Left Panel ---
        // This child window acts as a sidebar or tool panel.
        // The first parameter is the child name.
        // The second parameter is the size: width=200, height=remaining (0 means fill parent).
        // The third parameter 'true' enables a border.
        ImGui::BeginChild("LeftPanel", ImVec2(300, 0), true);
        ImGui::Text("This is the left panel.");
        ImGui::Button("Button 1");
        ImGui::EndChild();

        // Place the next child window to the right of the previous one.
        ImGui::SameLine();

        // --- Node Editor Panel ---
        // This child window fills the remaining space of the main window.
        // ImVec2(0, 0) means "use all available space".
        // This is where the node editor is rendered.
        ImGui::BeginChild("NodeEditorPanel", ImVec2(0, 0), true);

        // Set the current node editor context
        ed::SetCurrentEditor(editorContext);
        ed::Begin("My Editor");

        // Node 1
        ed::BeginNode(node_id_1);
        ImGui::Text("Node 1");
        ed::BeginPin(output_id, ed::PinKind::Output);
        ImGui::Text("Output");
        ed::EndPin();
        ed::EndNode();

        // Node 2
        ed::BeginNode(node_id_2);
        ImGui::Text("Node 2");
        ed::BeginPin(input_id, ed::PinKind::Input);
        ImGui::Text("Input");
        ed::EndPin();
        ed::EndNode();

        // Draw link if created
        if (link_created)
            ed::Link(link_id, output_id, input_id);

        // Example for handling new links (uncomment to enable link creation)
        // ed::PinId startPinId, endPinId;
        // if (ed::QueryNewLink(&startPinId, &endPinId)) {
        //     link_created = true;
        //     ed::AcceptNewItem();
        // }

        ed::End();
        ImGui::EndChild(); // End NodeEditorPanel

        ImGui::End(); // End MainWindow

        // --- Rendering ---
        ImGui::Render();
        glViewport(0, 0, 1280, 720);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup NodeEditor context
    ed::DestroyEditor(editorContext);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
