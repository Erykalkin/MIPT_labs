#include <iostream>


struct subforwardlist {
  int data;
  subforwardlist* next;
};


bool init(subforwardlist **sfl) {
  *sfl = NULL;
  return true;
} 	//инициализация пустого недосписка


bool push_back(subforwardlist **sfl, int d) {
  subforwardlist *pointer = *sfl;
  subforwardlist *a = new subforwardlist;

  if (*sfl == NULL) {
    *sfl = a;
    (*sfl)->data = d;
    (*sfl)->next = NULL;
    return true;

  } else {
    while (pointer->next != NULL) {
      pointer = pointer->next;
    }
    pointer->next = a;
    pointer->next->next = NULL;
    a->data = d;

    return true;
  }
}   //добавление элемента в конец недосписка


int pop_back(subforwardlist **sfl) {
  subforwardlist *pointer = *sfl;

  if (*sfl == NULL) {           
    return 0;

  } if ((*sfl)->next == NULL) {
    int deleted = (*sfl)->data;
    delete *sfl;
    *sfl = NULL;
    return deleted;

  } else {
    while (pointer->next->next != NULL) {
      pointer = pointer->next;
    }
    int deleted = pointer->next->data;
    delete pointer->next;
    pointer->next = NULL;

    return deleted;
  }
} 	//удаление элемента с конца недосписка, если пустой - возвращать 0


bool push_forward(subforwardlist **sfl, int d) {
  subforwardlist *a = *sfl;

  if (*sfl == NULL) {
    push_back(sfl, d);
    return true;
  } else {
    *sfl = new subforwardlist;
    (*sfl)->data = d;
    (*sfl)->next = a;
    return true;
  }
} 	//добавление элемента в начало недосписка


int pop_forward(subforwardlist **sfl) {
  if (*sfl == NULL) {           
    return 0;
  } else {
    subforwardlist *to_delete = *sfl;
    int deleted_value = to_delete->data;

    *sfl = (*sfl)->next; 
    delete to_delete;

    return deleted_value;
  }
}   //удаление элемента из начала недосписка, если пустой - возвращать 0


bool push_where(subforwardlist **sfl, unsigned int where, int d) {
  subforwardlist *pointer = *sfl;
  subforwardlist *a = new subforwardlist;

  if (where == 0) {
    return push_forward(sfl, d);
  }

  for (unsigned int i = 0; i < where-1; ++i) {
    pointer = pointer->next;
  }
  a->data = d;
  a->next = pointer->next;
  pointer->next = a;
  return true;
}   //добавление элемента с порядковым номером where


int erase_where(subforwardlist **sfl, unsigned int where) {
  subforwardlist *pointer = *sfl;

  if (where == 0) {
    return pop_forward(sfl);
  }

  for (unsigned int i = 0; i < where-1; ++i) {
    pointer = pointer->next;
  }

  if (pointer->next == NULL) {
    return 0;

  } else {
    int deleted = pointer->next->data;
    subforwardlist *bridge = pointer->next->next;
    delete pointer->next;
    pointer->next = bridge;

    return deleted;
  }
}	  //удаление элемента с порядковым номером where, если пустой - возвращать 0


unsigned int size(subforwardlist **sfl) {
  subforwardlist *pointer = *sfl;

  unsigned int i = 1;
  while (pointer != NULL) {
      pointer = pointer->next;
      ++i;
    }
  return i-1;
}	  //определить размер недосписка


void clear(subforwardlist **sfl) {
  while (*sfl != NULL) {
    pop_forward(sfl);
  }
}	  //очистить содержимое недосписка


void print(subforwardlist **sfl) {
  subforwardlist *pointer = *sfl;

  unsigned int n = size(sfl);
  for (unsigned int i = 0; i < n; ++i) {
    std::cout << pointer->data << ' ';
    pointer = pointer->next;
  }
  std::cout << std::endl;
}
