

#define TYPE double

struct Item {
    char* key;
    TYPE value;
};

typedef struct Item Item;

Item* newItem(char* key, TYPE val);
void heapSort(Item** nodeArr, int n);

