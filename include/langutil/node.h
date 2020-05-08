#pragma once

#include <vector>
#include <memory>
#include <functional>

namespace langutil {
    template <typename T>
    class Node {
    public:
        T type;
        Node *parent;
        std::vector<std::shared_ptr<Node>> children;

        virtual void verify() {
            for (const auto &child : children) {
                child.verify();
            }
        }

        Node *searchThis(const std::function<bool(Node *)> &checker) {
            for (std::shared_ptr<Node> &child : children) {
                if (checker(child.get()))
                    return child.get();
            }

            return nullptr;
        }

        Node *searchParent(const std::function<bool(Node *)> &checker) {
            if (!parent)
                return nullptr;

            for (const std::shared_ptr<Node> &child : parent->children) {
                if (checker(child.get()))
                    return child.get();
            }

            Node *parentSearch = parent->searchParent(checker);
            if (parentSearch)
                return parentSearch;

            return nullptr;
        }

        template <typename M>
        M *as() { return dynamic_cast<M *>(this); }

        Node(Node *parent, T type) : parent(parent), type(type) { }
        virtual ~Node() = default;
    };
}
