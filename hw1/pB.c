#include <stdio.h>
#include <stdlib.h>

long long shout(int arr[], int n, int k);

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("%lld\n", shout(arr, n, k));
    free(arr);
    return 0;
}

long long shout(int arr[], int n, int k) {
    if (n == 0) return 0;
    int max_a = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_a) max_a = arr[i];
    }
    if (max_a < k) return 0;

    long long *freq = (long long *)calloc(max_a + 1, sizeof(long long));
    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    long long *prefix = (long long *)calloc(max_a + 1, sizeof(long long));
    prefix[0] = freq[0];
    for (int x = 1; x <= max_a; x++) {
        prefix[x] = prefix[x - 1] + freq[x];
    }

    long long ans = 0;
    for (int p = k; p <= max_a; p++) {
        long long cur = 0;
        int v = 0;
        while (1) {
            int left = p * v;
            if (left > max_a) break;
            int right = p * (v + 1) - 1;
            if (right > max_a) right = max_a;
            long long cnt = prefix[right] - (left == 0 ? 0LL : prefix[left - 1]);
            cur += (long long)p * v * cnt;
            v++;
        }
        if (cur > ans) ans = cur;
    }

    free(freq);
    free(prefix);
    return ans;
}