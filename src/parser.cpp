#include <langutil/parser.h>

#include <algorithm>

namespace langutil {
    std::vector<char> Parser::defaultSymbols() {
        return std::vector<char> {
            ':',
            ';',
            ',',
            '.',
            '{',
            '}',
            '+',
            '-',
            '=',
            '/',
            '\\',
            '@',
            '#',
            '$',
            '%',
            '^',
            '&',
            '|',
            '*',
            '(',
            ')',
            '!',
            '?',
            '<',
            '>',
            '~',
            '[',
            ']',
            '\"',
            '\'',
        };
    }

    bool Parser::end(int offset) {
        return index + offset >= text.length();
    }

    bool Parser::strong(char c) {
        if (std::isspace(c))
            return true;

        return std::find(symbols.begin(), symbols.end(), c) != symbols.end();
    }

    void Parser::push() {
        if (!original)
            while (!end() && std::isspace(text[index])) { index++; }
    }

    int Parser::getIndex() {
        return index;
    }

    std::string Parser::getText() {
        return text;
    }

    bool Parser::empty(int offset) {
        push();
        return end(offset);
    }

    void Parser::rollback() {
        index = rollbackIndex;
    }

    void Parser::select() {
        selectIndex = index;
    }

    std::string Parser::clip() {
        return text.substr((unsigned long)selectIndex, (unsigned long)index - (unsigned long)selectIndex);
    }

    void Parser::back() {
        index = selectIndex;
    }

    std::string Parser::last() {
        int temp = index;

        while (index > 0 && std::isspace(text[index])) {
            index--;
        }

        if (!original) {
            while (index > 0 && !strong(text[index])) {
                index--;
            }
        }

        std::string word = next();
        rollback();

        rollbackIndex = temp;

        return word;
    }

    std::string Parser::until(const std::vector<std::string> &cases) {
        rollbackIndex = index;
        push();

        int length = 0;
        while (!empty(length)) {
            bool match = false;
            for (const std::string &test: cases) {
                if (text.substr(index + length, test.size()) == test) {
                    match = true;
                    break;
                }
            }

            if (match)
                break;

            length++;
        }

        std::string result;
        if (!empty())
            result = text.substr((unsigned long)index, (unsigned long)length);

        index += length;

        return result;
    }

    std::string Parser::next() {
        rollbackIndex = index;
        push();

        int length = 1;

        if (!empty(length) && !strong(text[index]))
            while (!empty(length) && !strong(text[index + length])) { length++; }

        if (empty())
            return "";

        std::string result = text.substr((unsigned long)index, (unsigned long)length);
        index += length;

        return result;
    }

    std::string Parser::peek() {
        int temp = rollbackIndex;

        std::string word = next();

        index = rollbackIndex;
        rollbackIndex = temp;

        return word;
    }

    Parser::Parser(std::string text) : Parser(move(text), defaultSymbols()) { }
    Parser::Parser(std::string text, std::vector<char> symbols) : text(move(text)), symbols(move(symbols)) { }
}
