struct subvector {
     int *mas;
     unsigned int top; 
     unsigned int capacity;
};


bool init (subvector *qv) {
  qv->capacity = 0;
  qv->top = 0;
  qv->mas = NULL;
  return true;
} // инициализация пустого недовектора (top и capacity по нулям, а mas это NULL)


bool resize (subvector *qv, unsigned int new_capacity) {
  int* s = new int[new_capacity];
  if (qv->capacity <= new_capacity) {
    for (unsigned int i = 0; i < qv->top; ++i) {
      s[i] = qv->mas[i];
    }
    qv->capacity = new_capacity;
  } else {
    for (unsigned int i = 0; i < new_capacity; ++i) {
      s[i] = qv->mas[i];
    }
    qv->capacity = new_capacity;
    qv->top = new_capacity;
  }

  delete[] qv->mas;
  qv->mas = s;
  return true;
} // увеличить емкость недовектора (можно использовать и для уменьшения - тогда, в рамках данной реализации, если top меньше новой capacity, то копируем только то, что влезает, и уменьшаем top до capacity)


bool push_back (subvector *qv, int d) {
  if (qv->top < qv->capacity) {
    qv->mas[qv->top] = d;
    qv->top += 1;
    return true;
  } else {
    resize(qv, qv->top+1);
    qv->mas[qv->top] = d;
    qv->top += 1;
    return true;
  }
} // добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости


int pop_back (subvector *qv) {
  if (qv->top != 0) {
    qv->top -= 1;
    return qv->mas[qv->top];
  }
  return 0;

} // удаление элемента с конца недовектора, значение удаленного элемента вернуть (если недовектор пустой, вернуть ноль)

void shrink_to_fit (subvector *qv) {
  int* s = new int[qv->top];
  for (unsigned int i = 0; i < qv->top; ++i) {
    s[i] = qv->mas[i];
  }
  delete[] qv->mas;
  qv->mas = s;
  qv->capacity = qv->top;
} // очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top


void clear (subvector *qv) {
  qv->top = 0;
} // очистить содержимое недовектора, занимаемое место при этом не меняется


void destructor (subvector *qv) {
  qv->top = 0;
  qv->capacity = 0;
  delete[] qv->mas;
}	// очистить всю используемую память, инициализировать недовектор как пустой
