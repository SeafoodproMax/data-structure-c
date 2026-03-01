//
// Created by 林勁博 on 2025/10/8.
//
#include <stdio.h>
#include <string.h>

#define maxn 400010
int pre[maxn], nxt[maxn], vals[maxn];

int main(void) {
    int N, Q;
    scanf("%d%d", &N, &Q);
    int cid = 1;
    int hd = 0, tl = 0;
    int i;
    for (i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        vals[cid] = x;
        pre[cid] = tl;
        nxt[cid] = 0;
        if (tl) nxt[tl] = cid;
        tl = cid;
        if (!hd) hd = cid;
        cid++;
    }
    for (i = 0; i < Q; i++) {
        char op[3];
        scanf("%s", op);
        if (strcmp(op, "H") == 0) {
            int x;
            scanf("%d", &x);
            int nid = cid++;
            vals[nid] = x;
            nxt[nid] = hd;
            pre[nid] = 0;
            if (hd) pre[hd] = nid;
            hd = nid;
            if (!tl) tl = nid;
        } else if (strcmp(op, "T") == 0) {
            int x;
            scanf("%d", &x);
            int nid = cid++;
            vals[nid] = x;
            pre[nid] = tl;
            nxt[nid] = 0;
            if (tl) nxt[tl] = nid;
            tl = nid;
            if (!hd) hd = nid;
        } else if (strcmp(op, "A") == 0) {
            int k, x;
            scanf("%d%d", &k, &x);
            int nid = cid++;
            vals[nid] = x;
            nxt[nid] = nxt[k];
            pre[nid] = k;
            if (nxt[k]) pre[nxt[k]] = nid;
            nxt[k] = nid;
            if (tl == k) tl = nid;
        } else if (strcmp(op, "B") == 0) {
            int k, x;
            scanf("%d%d", &k, &x);
            int nid = cid++;
            vals[nid] = x;
            nxt[nid] = k;
            pre[nid] = pre[k];
            if (pre[k]) nxt[pre[k]] = nid;
            pre[k] = nid;
            if (hd == k) hd = nid;
        } else if (strcmp(op, "D") == 0) {
            int k;
            scanf("%d", &k);
            if (pre[k]) nxt[pre[k]] = nxt[k];
            if (nxt[k]) pre[nxt[k]] = pre[k];
            if (hd == k) hd = nxt[k];
            if (tl == k) tl = pre[k];
        } else if (strcmp(op, "MH") == 0) {
            int k;
            scanf("%d", &k);
            // remove
            int p = pre[k];
            int n = nxt[k];
            if (p) nxt[p] = n;
            if (n) pre[n] = p;
            if (hd == k) hd = n;
            if (tl == k) tl = p;
            // insert head
            nxt[k] = hd;
            pre[k] = 0;
            if (hd) pre[hd] = k;
            hd = k;
            if (!tl) tl = k;
        } else if (strcmp(op, "MT") == 0) {
            int k;
            scanf("%d", &k);
            // remove
            int p = pre[k];
            int n = nxt[k];
            if (p) nxt[p] = n;
            if (n) pre[n] = p;
            if (hd == k) hd = n;
            if (tl == k) tl = p;
            // insert tail
            pre[k] = tl;
            nxt[k] = 0;
            if (tl) nxt[tl] = k;
            tl = k;
            if (!hd) hd = k;
        }
    }
    if (!hd) {
        printf("EMPTY\nEMPTY\n");
    } else {
        int cur = hd;
        while (cur) {
            printf("%d", vals[cur]);
            cur = nxt[cur];
            if (cur) printf(" ");
            else printf("\n");
        }
        cur = tl;
        while (cur) {
            printf("%d", vals[cur]);
            cur = pre[cur];
            if (cur) printf(" ");
            else printf("\n");
        }
    }
    return 0;
}