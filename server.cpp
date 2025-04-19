#include "crow_all.h"
#include <string>
#include <vector>

class TextEditor {
    std::vector<std::string> history;
    int current;

public:
    TextEditor() : current(0) {
        history.push_back("");
    }

    void type(const std::string& text) {
        history.resize(current + 1);
        history.push_back(history[current] + text);
        current++;
    }

    void undo() {
        if (current > 0) current--;
    }

    void redo() {
        if (current < (int)history.size() - 1) current++;
    }

    std::string getText() const {
        return history[current];
    }
};

int main() {
    crow::SimpleApp app;
    TextEditor editor;

    CROW_ROUTE(app, "/add").methods("POST"_method)([&editor](const crow::request& req){
        auto text = req.body;
        editor.type(text);
        return crow::response("Text added");
    });

    CROW_ROUTE(app, "/undo")([&editor](){
        editor.undo();
        return crow::response("Undo");
    });

    CROW_ROUTE(app, "/redo")([&editor](){
        editor.redo();
        return crow::response("Redo");
    });

    CROW_ROUTE(app, "/text")([&editor](){
        return crow::response(editor.getText());
    });

    app.port(18080).multithreaded().run();
}
