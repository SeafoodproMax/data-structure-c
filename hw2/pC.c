#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXLEN 10005
#define MAXTOK 10005

typedef struct Token {
    int type;   // 1 = number, 2 = operator, 3 = parentheses
    char ch;    // operator or parentheses
    int num;    // number
} Token;

Token input[MAXTOK];
int input_len = 0;

/* ---------- 初始化 ---------- */
void init() {
    input_len = 0;
    for (int i = 0; i < MAXTOK; i++) {
        input[i].type = 0;
        input[i].ch = '\0';
        input[i].num = 0;
    }
}

/* ---------- 以空白分隔的 tokenizer（最穩） ---------- */
void getInput() {
    char line[MAXLEN];
    if (!fgets(line, sizeof(line), stdin)) return;

    // 去尾端換行
    size_t L = strlen(line);
    if (L && (line[L-1] == '\n' || line[L-1] == '\r')) line[--L] = '\0';

    char *tok = strtok(line, " \t\r\n");
    while (tok && input_len < MAXTOK) {
        if ((tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/' ||
             tok[0] == '(' || tok[0] == ')') && tok[1] == '\0') {
            // 單字元運算子或括號
            input[input_len].ch = tok[0];
            if (tok[0] == '(' || tok[0] == ')') input[input_len].type = 3;
            else input[input_len].type = 2;
            input_len++;
        } else {
            // 數字（多位數 OK）
            // 題目保證運算元是非負整數
            char *endp;
            long v = strtol(tok, &endp, 10);
            // 防呆：若不是純數字，直接忽略（競賽環境下也可 assert）
            if (*endp == '\0') {
                input[input_len].type = 1;
                input[input_len].num = (int)v;
                input_len++;
            }
        }
        tok = strtok(NULL, " \t\r\n");
    }
}

/* ---------- Stack<Token> ---------- */
typedef struct Stack {
    Token data[MAXTOK];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
bool isEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, Token t) { s->data[++s->top] = t; }
Token pop(Stack *s) { return s->data[s->top--]; }
Token peek(Stack *s) { return s->data[s->top]; }

/* ---------- 優先級 ---------- */
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

/* ---------- Infix → Postfix（Shunting-yard） ---------- */
int infixToPostfix(Token *infix, int n, Token *postfix) {
    Stack ops; initStack(&ops);
    int out_len = 0;

    for (int i = 0; i < n; i++) {
        Token cur = infix[i];
        if (cur.type == 1) {
            postfix[out_len++] = cur;
        } else if (cur.type == 2) {
            while (!isEmpty(&ops) && peek(&ops).ch != '(' &&
                   precedence(peek(&ops).ch) >= precedence(cur.ch)) {
                postfix[out_len++] = pop(&ops);
            }
            push(&ops, cur);
        } else if (cur.type == 3 && cur.ch == '(') {
            push(&ops, cur);
        } else if (cur.type == 3 && cur.ch == ')') {
            while (!isEmpty(&ops) && peek(&ops).ch != '(')
                postfix[out_len++] = pop(&ops);
            if (!isEmpty(&ops) && peek(&ops).ch == '(') pop(&ops); // 丟 '('
        }
    }
    while (!isEmpty(&ops)) postfix[out_len++] = pop(&ops);
    return out_len;
}

/* ---------- 用 Postfix 建樹 ---------- */
typedef struct Node {
    bool isOp;
    char op;
    int val;
    struct Node *left, *right;
} Node;

Node* newNodeNum(int v) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->isOp = false; p->op = 0; p->val = v; p->left = p->right = NULL;
    return p;
}
Node* newNodeOp(char op, Node *l, Node *r) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->isOp = true; p->op = op; p->val = 0; p->left = l; p->right = r;
    return p;
}
Node* buildTreeFromPostfix(Token *pf, int n) {
    Node* st[MAXTOK]; int top = -1;
    for (int i = 0; i < n; i++) {
        if (pf[i].type == 1) {
            st[++top] = newNodeNum(pf[i].num);
        } else {
            Node *r = st[top--];
            Node *l = st[top--];
            st[++top] = newNodeOp(pf[i].ch, l, r);
        }
    }
    return st[top];
}

/* ---------- 計算值（後序） ---------- */
int eval(Node *root) {
    if (!root->isOp) return root->val;
    int a = eval(root->left), b = eval(root->right);
    switch (root->op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b; // 題目保證向零取整、且不會除以 0
    }
    return 0;
}

/* ---------- 輸出前序（prefix） ---------- */
void preorder(Node *root) {
    if (!root) return;
    if (root->isOp) printf("%c ", root->op);
    else            printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    init();
    getInput();

    Token postfix[MAXTOK];
    int pf_len = infixToPostfix(input, input_len, postfix);

    Node *root = buildTreeFromPostfix(postfix, pf_len);
    int res = eval(root);

    // 第一行：結果
    printf("%d\n", res);
    // 第二行：前序
    preorder(root);
    printf("\n");
    return 0;
}