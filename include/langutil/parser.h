#pragma once

#include <string>
#include <vector>

namespace langutil {
    class Parser {
        int rollbackIndex = 0;
        int index = 0;
        std::string text;

        int selectIndex = 0;

        bool end(int offset = 0);
        bool strong(char c);
        void push();

    public:
        bool original = false;
        std::vector<char> symbols;

        static std::vector<char> defaultSymbols();

        int getIndex();
        std::string getText();

        bool empty(int offset = 0);

        void rollback();

        void select();
        std::string clip();
        void back();

        std::string last();
        std::string next();
        std::string peek();
        std::string until(const std::vector<std::string> &cases);

        explicit Parser(std::string text);
        Parser(std::string text, std::vector<char> symbols);
    };
}
