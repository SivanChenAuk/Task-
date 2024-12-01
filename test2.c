#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1000  // 定义最大输入长度

// 定义哈夫曼树节点结构
typedef struct Node {
    char data;          // 字符
    int frequency;      // 频率
    struct Node *left;  // 左子节点
    struct Node *right; // 右子节点
} Node;

// 定义最小堆节点数组
Node* minHeap[128];
int heapSize = 0;

// 创建新节点
Node* createNode(char data, int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->frequency = freq;
    node->left = node->right = NULL;
    return node;
}

// 最小堆操作
void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heapSize && minHeap[left]->frequency < minHeap[smallest]->frequency)
        smallest = left;
    if (right < heapSize && minHeap[right]->frequency < minHeap[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap[idx], &minHeap[smallest]);
        minHeapify(smallest);
    }
}

void insertMinHeap(Node* node) {
    minHeap[heapSize] = node;
    int current = heapSize;
    heapSize++;

    while (current > 0 && minHeap[(current - 1) / 2]->frequency > minHeap[current]->frequency) {
        swap(&minHeap[(current - 1) / 2], &minHeap[current]);
        current = (current - 1) / 2;
    }
}

Node* extractMin() {
    if (heapSize <= 0) return NULL;
    
    Node* temp = minHeap[0];
    minHeap[0] = minHeap[heapSize - 1];
    heapSize--;
    minHeapify(0);
    
    return temp;
}

// 统计字符频率
void countFrequency(const char* str, int* freq) {
    for (int i = 0; str[i]; i++) {
        freq[(unsigned char)str[i]]++;
    }
}

// 构建哈夫曼树
Node* buildHuffmanTree(int* freq) {
    // 创建叶节点并插入最小堆
    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            Node* node = createNode(i, freq[i]);
            insertMinHeap(node);
        }
    }

    // 构建哈夫曼树
    while (heapSize > 1) {
        Node* left = extractMin();
        Node* right = extractMin();
        
        Node* parent = createNode('$', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        insertMinHeap(parent);
    }

    return extractMin();
}

// 打印哈夫曼编码
void printCodes(Node* root, int* code, int top) {
    if (root->left) {
        code[top] = 0;
        printCodes(root->left, code, top + 1);
    }
    
    if (root->right) {
        code[top] = 1;
        printCodes(root->right, code, top + 1);
    }
    
    if (!root->left && !root->right) {
        printf("'%c': ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", code[i]);
        printf(" (频率: %d)\n", root->frequency);
    }
}

// 修改main函数
int main() {
    char input[MAX_INPUT_LENGTH];  // 输入缓冲区
    int freq[128] = {0};          // ASCII字符频率数组
    
    // 获取用户输入
    printf("请输入要编码的字符串：");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("读取输入失败\n");
        return 1;
    }
    
    // 移除输入字符串末尾的换行符
    input[strcspn(input, "\n")] = '\0';
    
    // 检查输入是否为空
    if (strlen(input) == 0) {
        printf("输入为空\n");
        return 1;
    }
    
    // 统计频率
    countFrequency(input, freq);
    
    // 构建哈夫曼树
    Node* root = buildHuffmanTree(freq);
    if (root == NULL) {
        printf("构建哈夫曼树失败\n");
        return 1;
    }
    
    // 打印原始字符串
    printf("\n原始字符串：%s\n", input);
    printf("字符串长度：%zu\n\n", strlen(input));
    
    // 打印编码
    printf("Huffman编码结果:\n");
    int code[100], top = 0;
    printCodes(root, code, top);
    
    // 释放内存
    // TODO: 添加释放哈夫曼树的函数
    
    return 0;
}

// 添加释放哈夫曼树的函数
void freeHuffmanTree(Node* root) {
    if (root == NULL) return;
    
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    free(root);
}