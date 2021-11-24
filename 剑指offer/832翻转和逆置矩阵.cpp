class Solution
{
public:
    void SwapAndInvert(vector<int> &A)
    {
        int l = 0, r = A.size() - 1;
        while (l <= r)
        {
            if (l != r)
                A[l] = A[l] ^ 1;
            A[r] = A[r] ^ 1;
            swap(A[l], A[r]);
            l++;
            r--;
        }
    }

    vector<vector<int>> flipAndInvertImage(vector<vector<int>> &A)
    {
        for (auto &item : A)
            SwapAndInvert(item);
        return A;
    }
};
