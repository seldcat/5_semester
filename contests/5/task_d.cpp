#include <iostream>
#include <memory>
#include <optional>
#include <vector>

struct Node {
  uint32_t key, priority;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
  
  Node() {}
  Node(uint32_t key, uint32_t priority): key(key), priority(priority), left(nullptr), right(nullptr) {}
  Node(std::unique_ptr<Node> pnode): key(pnode->key), priority(pnode->priority), left(pnode->left)  {}
};
typedef std::unique_ptr<Node> pNode;

class Treap {
  public:
    Treap(): root_(nullptr) {}
    
  private:
    void Split(pNode node, uint32_t key, pNode &left, pNode &right) {
      if (!node) {
        left = nullptr;
        right = nullptr;
        return;
      }
      if (key < node->key) {
        split(node->left, key, left, node->left);
        
      }
    }
    
    pNode root_;
};
