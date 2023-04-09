#include <iostream>
#include "subforwardlist.h"


struct subset_node {
  int key;
  subset_node *left = NULL;
  subset_node *right = NULL;
  subset_node *parent = NULL;
  bool marked = false;
}; // можете добавлять дополнительные поля


bool init(subset_node **sn) {
  *sn = NULL;
  return true;
} // инициализация пустого дерева (аналогично списку, пустое дерево это указатель на NULL)


void print_node(subset_node *node) {
  std::cout << "key: " << node->key << '\n';

  if (node->parent != NULL) {
    std::cout << "parent key: " << node->parent->key << '\n';
  }
  else {
    std::cout << "parent doesn't exist!\n";
  }

  if (node->left != NULL) {
    std::cout << "letf child key: " << node->left->key << '\n';
  }
  else {
    std::cout << "left child doesn't exist!\n";
  }

  if (node->right != NULL) {
    std::cout << "right child key: " << node->right->key << '\n';
  }
  else {
    std::cout << "right child doesn't exist!\n";
  }
}


subset_node* find(subset_node *sn, int k) {
  if (sn == NULL) {
    return NULL;
  }

  if (k < sn->key) {
    return find(sn->left, k);
  }

  if (k > sn->key) {
    return find(sn->right, k);
  }
  
  return sn;
} // поиск элемента в дереве, нужно вернуть указатель на элемент с тем же key или, если такого элемента не нашлось, то NULL


unsigned int size_f(subset_node *sn, unsigned int n) {
  if (sn != NULL) {
    ++n;
  }
  if (sn->left != NULL) {
    n = size_f(sn->left, n);
  }
  if (sn->right != NULL) {
    n = size_f(sn->right, n);
  }
  return n;
}


unsigned int size(subset_node *sn) {
  unsigned int n = 0;
  if (sn == NULL) {
    return n;
  }
  return size_f(sn, n);
} // количество элементов в дереве


unsigned int height_f(subset_node *sn, unsigned int n) {
  if (sn != NULL) {
    ++n;
  }
  if (sn->left != NULL && sn->right != NULL) {
    if (height_f(sn->left, n) > height_f(sn->right, n)) {
      n = height_f(sn->left, n);
    }
    else {
      n = height_f(sn->right, n);
    }
  }
  if (sn->left == NULL && sn->right != NULL) {
    n = height_f(sn->right, n);
  }
  if (sn->left != NULL && sn->right == NULL) {
    n = height_f(sn->left, n);
  }
  return n;
}


unsigned int height(subset_node *sn) {
  unsigned int n = 0;
  if (sn == NULL) {
    return n;
  }
  return height_f(sn, n);
} // высота дерева


bool insert(subset_node **sn, int k, subset_node *p = NULL) {
  if (*sn == NULL) {
    subset_node *mem = new subset_node;
    *sn = mem;
    (*sn)->key = k;
    (*sn)->left = NULL;
    (*sn)->right = NULL;
    (*sn)->parent = p;
    return true;
  }
  if (k < (*sn)->key) {
    return insert(&((*sn)->left), k, *sn);
  }
  if (k > (*sn)->key) {
    return insert(&((*sn)->right), k, *sn);
  }
  else {
    return false;
  }
} // добавление элемента в дерево, дубли игнорировать (ничего не добавлять в дерево, если там уже есть элемент с таким же key) и возвращать false


void bridge(subset_node **b, subset_node **l, subset_node **r, bool is_left) {
  if (is_left) {
    if (*l != NULL && *r != NULL) {
      subset_node *pointer = *r;
      while (pointer->left != NULL) {
        pointer = pointer->left;
      }

      // if (pointer->key == (*r)->key) {
      //   pointer->parent->right = NULL;
      // }

      if (pointer->key != (*r)->key) {
        pointer->parent->left = pointer->right;

        if (pointer->right != NULL) {
          pointer->right->parent = pointer->parent;
        }

        pointer->right = *r;
        (*r)->parent = pointer;
      }

      pointer->left = *l;
      (*l)->parent = pointer;

      if (b != NULL) {
        (*b)->left = pointer;
        pointer->parent = *b;
      }

      else {
        pointer->parent = NULL;
      }
    }

    else if (*l == NULL && *r != NULL) {
      if (b != NULL) {
        (*b)->left = *r;
        (*r)->parent = *b;
      }
    }

    else if (*l != NULL && *r == NULL) {
      if (b != NULL) {
        (*b)->left = *l;
        (*l)->parent = *b;
      }
    }

    else if (b != NULL) {
      (*b)->left = NULL;
    }
  }

  else {
    if (*l != NULL && *r != NULL) {
      subset_node *pointer = *l;
      while (pointer->right != NULL) {
        pointer = pointer->right;
      }

      // if (pointer->key == (*l)->key) {
      //   pointer->parent->left = NULL;
      // }

      if (pointer->key != (*l)->key) {
        pointer->parent->right = pointer->left;

        if (pointer->left != NULL) {
          pointer->left->parent = pointer->parent;
        }

        pointer->left = *l;
        (*l)->parent = pointer;
      }

      pointer->right = *r;
      (*r)->parent = pointer;

      if (b != NULL) {
        (*b)->right = pointer;
        pointer->parent = *b;
      }

      else {
        pointer->parent = NULL;
      }
    }

    else if (*l == NULL && *r != NULL) {
      if (b != NULL) {
        (*b)->right = *r;
        (*r)->parent = *b;
      }
    }

    else if (*l != NULL && *r == NULL) {
      if (b != NULL) {
        (*b)->right = *l;
        (*l)->parent = *b;
      }
    }

    else if (b != NULL) {
      (*b)->right = NULL;
    }
  }
}


bool remove(subset_node **sn, int k) {
  if ((*sn) == NULL) {
    return false;
  }

  if (k < (*sn)->key) {
    return remove(&((*sn)->left), k);
  }

  if (k > (*sn)->key) {
    return remove(&((*sn)->right), k);
  }
  
  subset_node *parent = (*sn)->parent;
  subset_node *l = (*sn)->left;
  subset_node *r = (*sn)->right;

  if (parent == NULL) {
    subset_node *del = *sn;
    bool go_left = height((*sn)->left) > height((*sn)->right);

    if (go_left) {
      bridge(NULL, &l, &r, false);
    }
    else {
      bridge(NULL, &l, &r, true);
    }
    
    if (l != NULL && r != NULL && go_left) {
      *sn = r->parent;
    }
    else if (l != NULL && r != NULL && !go_left) {
      *sn = l->parent;
    }
    else if (l == NULL && r != NULL) {
      *sn = r;
      (*sn)->parent = NULL;
    }
    else if (l != NULL && r == NULL) {
      *sn = l;
      (*sn)->parent = NULL;
    }
    else if (l == NULL && r == NULL) {
      *sn = NULL;
    }

    delete del;
    return true;
  }

  bool is_left_child = (*sn)->key < parent->key;

  subset_node *del = *sn;

  bridge(&parent, &l, &r, is_left_child);

  delete del;

  return true;
} // удаление элемента из дерева (если элемента не нашлось, то ничего не удалять и вернуть false)


void destructor(subset_node *sn) {
  if (sn->left != NULL) {
    destructor(sn->left);
  }
  if (sn->right != NULL) {
    destructor(sn->right);
  }
  delete sn;
} // очистить всю используемую память


int *from_SFL_to_int(subforwardlist **keys) {
  unsigned int s = size(keys);
  int *k = new int[s];
  for (unsigned int i = 0; i < s; ++i) {
    k[i] = pop_forward(keys);
  }
  return k;
}


subforwardlist **DFS_f(subset_node *sn, subforwardlist **keys) {
  if (sn->left != NULL) {
    DFS_f(sn->left, keys);
  }
  push_back(keys, sn->key);
  if (sn->right != NULL) {
    DFS_f(sn->right, keys);
  }
  return keys;
}


int *DFS(subset_node *sn) {
  subforwardlist *keys;
  init(&keys);
  return from_SFL_to_int(DFS_f(sn, &keys));
} // обход в глубину, возвращает указатель на массив


// HardMode

// void roots(subset_node *sn, unsigned int k) {
//   if (k > 1) {
//     for (unsigned int i = 0; i < k; ++i) {
//       std::cout << "-";
//     }
//     for (unsigned int i = 0; i < k; ++i) {
//       std::cout << "|" << std::endl;
//     }
//     std::cout << sn->key << std::endl;
//     for (unsigned int i = 0; i < k; ++i) {
//       std::cout << "|" << std::endl;
//     }
//     for (unsigned int i = 0; i < k; ++i) {
//       std::cout << "-";
//     }
//   } else {
//     std::cout << "|" << std::endl;

//   }
// }

// void print_subset(subset_node *sn) {
//   unsigned int k = 5;
//   if (sn == NULL) {
//     return;
//   }

//} // вывод дерева на экран в удобном читаемом виде, это поможет вам при отладке функций, перечисленных ниже

// int* BFS (subset_node *sn) {
// } //обход в ширину, возвращает указатель на массив

// subset_node* merge(subset_node *sn1, subset_node *sn2) {
// } // слияние двух деревьев