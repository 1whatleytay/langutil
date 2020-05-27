#pragma once

#include <string>
#include <vector>

namespace langutil {
    class Parser {
        size_t rollbackIndex = 0;
        size_t index = 0;
        std::string text;

        size_t selectIndex = 0;

        bool end(size_t offset = 0);
        bool strong(char c);
        void push();

    public:
        bool original = false;
        std::vector<char> symbols;

        static std::vector<char> defaultSymbols();

        std::string content();

        bool empty(size_t offset = 0);

        void rollback();

        size_t select();
        std::string clip();
        void back();
        void jump(size_t offset);

        std::string last();
        std::string next();
        std::string peek();
        std::string until(const std::vector<std::string> &cases);

        explicit Parser(std::string text);
        Parser(std::string text, std::vector<char> symbols);
    };
}
