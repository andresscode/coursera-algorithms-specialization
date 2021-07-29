from __future__ import annotations


class Node:
    def __init__(self, key=None, parent=None):
        self.key = key
        self.parent = parent
        self.children = {}
        self.flag = False


class Trie:
    def __init__(self, patterns):
        self.root = Node()
        for pattern in patterns:
            current_node = self.root
            for letter in pattern:
                if letter not in current_node.children:
                    current_node.children[letter] = Node(
                        key=letter, parent=current_node)
                current_node = current_node.children[letter]
            current_node.flag = True

    def find_matches(self, text):
        t = text
        while t:
            self.__find(t)
            t = t[1:]

    def __find(self, text):
        current_node = self.root
        for letter in text:
            if letter in current_node.children:
                current_node = current_node.children[letter]
            else:
                break
        if current_node.flag:
            print(self.__reconstruct_path(current_node))

    def words(self):
        self.__dfs(self.root)

    def __dfs(self, node):
        if node.key and node.flag:
            print(self.__reconstruct_path(node))
        for child in node.children.values():
            self.__dfs(child)

    def __reconstruct_path(self, node):
        letters = []
        current = node
        while current.key:
            letters.append(current.key)
            current = current.parent
        return ''.join(reversed(letters))
