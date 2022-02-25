#include <iostream>

using namespace std;
int brk = 0;

bool bo_is_reflexive(int N, int** a)
{
    int res = 0;

    for (int i = 0; i < N; ++i)
    {
        if (a[i][i] == 1)
            res = 1;
        else res = 0;

        if (res == 0)
        {
            return  res;
        }
    }

    return  res;
}

bool bo_is_antireflexive(int N, int** a)
{
    int res = 0;

    for (int i = 0; i < N; ++i)
    {
        if (a[i][i] == 0)
            res = 1;
        else res = 0;

        if (res == 0)
        {
            return  res;
        }
    }

    return  res;
}

bool bo_is_symmetric(int N, int** a)
{
    int res = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            if (a[i][j] == a[j][i])
                res = 1;
            else res = 0;

            if (res == 0)
            {
                return  res;
            }
        }
    }

    return  res;
}

bool bo_is_antisymmetric(int N, int** a)
{
    int res = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            if (a[i][j] == 1 && a[j][i] == 1) {
                if (i == j)
                    res = 1;
                else res = 0;
            }
            else res = 1;

            if (res == 0)
            {
                return  res;
            }
        }
    }

    return  res;
}

bool bo_is_transitive(int N, int** a)
{
    int res = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                if (a[i][j] >= a[i][k] * a[k][j])
                    res = 1;
                else res = 0;

                if (res == 0)
                {
                    return  res;
                }
            }
        }
    }

    return  res;
}

//строим замыкания
void z_reflexive(int N, int** a)
{
    for (int i = 0; i < N; i++)
    {
        a[i][i] = 1;
    }
}

void z_sim(int N, int** a)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (a[i][j] == 1)
                a[j][i] = 1;
        }
    }
}

void z_tranz(int N, int** a)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                if (a[j][k] == 1)
                    for (int d = 0; d < N; d++)
                        if (a[k][d] == 1)
                            a[j][d] = 1;

}


void z_build(int N, int** a, int vvod)
{
    int** z_a;
    z_a = new int* [N];
    for (int i = 0; i < N; i++) {
        z_a[i] = new int[N];
        for (int j = 0; j < N; j++) {
            z_a[i][j] = a[i][j];
        }
    }
    switch (vvod)
    {
    case 1:
        z_reflexive(N, z_a);
        break;
    case 2:
        z_sim(N, z_a);
        break;
    case 3:
        z_tranz(N, z_a);
        break;
    case 4:
        z_reflexive(N, z_a);
        z_sim(N, z_a);
        z_tranz(N, z_a);
        break;
    case 5:
        brk = 1;
        break;
    default:
        cout << "Error" << endl;
        break;
    }
    if (brk == 0) {
        cout << "Построенное замыкание:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << z_a[i][j] << ' ';
            cout << endl;
        }
    }
}

void    bo_result(int N, int** a)
{
    cout << "Введеная матрица:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
    int res_refl = bo_is_reflexive(N, a);
    int res_antirefl = bo_is_antireflexive(N, a);
    int res_simm = bo_is_symmetric(N, a);
    int res_antisimm = bo_is_antisymmetric(N, a);
    int res_tranz = bo_is_transitive(N, a);
    cout << "Результаты (1 - да, 0 - нет):" << endl;
    cout << "Рефлексивность:" << res_refl << endl;
    cout << "Антирефлексивность:" << res_antirefl << endl;
    cout << "Симметричность:" << res_simm << endl;
    cout << "Антисимметричность:" << res_antisimm << endl;
    cout << "Транзитивность:" << res_tranz << endl;

    if (res_refl == 1 && res_tranz == 1) {
        cout << "Данное отношение является отношением квазипорядка" << endl;
        if (res_simm == 1)
            cout << "Данное отношение является отношением эквивалентности" << endl;
    }
    if (res_refl == 1 && res_antisimm == 1 && res_tranz == 1) {
        cout << "Данное отношение является отношением порядка" << endl;
    }

    int vvod;
    cout << "Введите, какое замыкание требуется построить:" << endl;
    cout << "1 - рефлексивное" << endl << "2 - симметричное" << endl << "3 - транзитивное" << endl << "4 - эквивалентное" << endl << "5 - не строить никакое замыкание" << endl;
    while (brk == 0) {
        cout << "Введите номер:" << endl;
        cin >> vvod;
        z_build(N, a, vvod);
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");

    int sposob, i, j, N;
    cout << "Введите способ ввода (1 - поэлементно, 2 - построчно): "; cin >> sposob;
    cout << "Введите размерность матрицы бинарного отношения: "; cin >> N;
    int** a;
    a = new int* [N];
    cout << "Введите матрицу А" << endl;
    if (sposob == 1) {
        for (i = 0; i < N; i++) {
            a[i] = new int[N];
            for (j = 0; j < N; j++) {
                cout << "A["
                    << i
                    << "]["
                    << j
                    << "] = ";
                cin >> a[i][j];
            }
        }
    }
    else
    {
        for (int i = 0; i < N; i++) {
            a[i] = new int[N];
            for (int j = 0; j < N; j++) {
                cin >> a[i][j];
            }
        }
    }

    cout << endl;
    bo_result(N, a);
    cout << endl;
}
