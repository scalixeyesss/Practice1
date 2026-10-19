#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
using namespace std;



void free_matrix(int **a, size_t n)
{
    if (a == nullptr)
        return;
    for (size_t i = 0; i < n; ++i)
        delete[] a[i];
    delete[] a;
}



int **concat_rows(const int *const *lhs, size_t n1, size_t m1,
                  const int *const *rhs, size_t n2, size_t m2)
{
    if (numeric_limits<size_t>::max() - m1 < m2)
        throw overflow_error("overflow in m1 + m2");

    size_t n = n1 > n2 ? n1 : n2;
    int **res = new int *[n]();
    try
    {
        for (size_t i = 0; i < n; ++i)
        {
            size_t len1 = i < n1 ? m1 : 0;
            size_t len2 = i < n2 ? m2 : 0; 
            res[i] = new int[len1 + len2];
            for (size_t j = 0; j < len1; ++j)
                res[i][j] = lhs[i][j];
            for (size_t j = 0; j < len2; ++j)
                res[i][len1 + j] = rhs[i][j];
        }
    }
    catch (...)
    {
        free_matrix(res, n);
        throw;               
    }
    return res;
}

int **read_matrix(size_t *n, size_t *m)
{
    long long a, b;
    if (!(cin >> a >> b) || a <= 0 || b <= 0)
        throw invalid_argument("bad size");
    *n = a;
    *m = b;

    int **mat = new int *[*n]();
    try
    {
        for (size_t i = 0; i < *n; ++i)
        {
            mat[i] = new int[*m];
            for (size_t j = 0; j < *m; ++j)
                if (!(cin >> mat[i][j]))
                    throw invalid_argument("bad element");
        }
    }
    catch (...)
    {
        free_matrix(mat, *n);
        throw;
    }
    return mat;
}

int main()
{
    size_t n1 = 0, m1 = 0, n2 = 0, m2 = 0, n = 0;
    int **lhs = nullptr, **rhs = nullptr, **res = nullptr;
    int rc = 0;

    try
    {
        cout << "Матрица 1: n1 m1, затем числа\n";
        lhs = read_matrix(&n1, &m1);
        cout << "Матрица 2: n2 m2, затем числа\n";
        rhs = read_matrix(&n2, &m2);

        res = concat_rows(lhs, n1, m1, rhs, n2, m2);

        n = n1 > n2 ? n1 : n2;
        for (size_t i = 0; i < n; ++i)
        {
            size_t len = (i < n1 ? m1 : 0) + (i < n2 ? m2 : 0);
            for (size_t j = 0; j < len; ++j)
            {
                if (j > 0)
                    cout << ' ';
                cout << res[i][j];
            }
            cout << '\n';
        }
    }
    catch (const overflow_error &)
    {
        cerr << "Ошибка памяти: переполнение размера\n";
        rc = 2;
    }
    catch (const bad_alloc &)
    {
        cerr << "Ошибка памяти\n";
        rc = 2;
    }
    catch (const invalid_argument &)
    {
        cerr << "Ошибка ввода\n";
        rc = 1;
    }

    free_matrix(res, n);
    free_matrix(rhs, n2);
    free_matrix(lhs, n1);
    return rc;
}