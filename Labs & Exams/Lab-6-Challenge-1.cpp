#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * TODO: Implement function templates map and fold here.
 */

/* The map function being implemented */
template <template <class, class> class Container, class ElemType, class Type, class MapFunction>
Container<ElemType, Type> map(Container<ElemType, Type> &c, MapFunction)
{
    Container<ElemType, Type> v(c.size());                   // defined the sub vector
    transform(c.begin(), c.end(), v.begin(), MapFunction()); // applying the transform function
    return v;
}

/* The fold function being implemented */
template <template <class, class> class Container, class ElemType, class Type, class InitialValue, class FoldFunction>
InitialValue fold(Container<ElemType, Type> &c, InitialValue init, FoldFunction func)
{
    // defining the Helper function for helping in the binary to unary operations
    class FoldHelper
    {
    private:
        InitialValue init;
        FoldFunction func;

    public:
        FoldHelper(InitialValue &initVal, FoldFunction f)
        {
            init = (initVal);
            func = f;
        }
        InitialValue operator()(ElemType elem)
        {
            init = func(init, elem);
            return init;
        }
    };
    FoldHelper F(init, func);
    vector<InitialValue> v(c.size());
    transform(c.begin(), c.end(), v.begin(), F); // transforming using the helper function
    InitialValue returnValue = *(--v.end());
    return returnValue;
}

/* Mapping Functions */

class MapF0
{
public:
    int operator()(int elem)
    {
        return ++elem;
    }
};

class MapF1
{
public:
    string operator()(string elem)
    {
        return elem + "abc";
    }
};

class MapF2
{
public:
    vector<int> operator()(vector<int> elem)
    {
        elem.push_back(0);
        return elem;
    }
};

/* Folding functions */

class FoldOp0
{
public:
    int operator()(int arg1, int arg2)
    {
        return arg1 * arg2;
    }
};

class FoldOp1
{
public:
    string operator()(string arg1, int arg2)
    {
        string arg3 = arg1;

        for (int i = 0; i < arg2; i++)
        {
            arg3 += arg1;
        }
        return arg3;
    }
};

class FoldOp2
{
public:
    vector<int> operator()(vector<int> arg1, vector<int> arg2)
    {
        vector<int> arg3;
        for (int i = 0; i < arg1.size(); i++)
        {
            arg3.push_back(arg1[i] + arg2[i]);
        }
        return arg3;
    }
};

class FoldOp3
{
public:
    int operator()(int arg1, int arg2)
    {
        return arg1 * arg2;
    }
};

class FoldOp4
{
public:
    int operator()(int arg1, int arg2)
    {
        return arg1 % arg2;
    }
};

/* Starter Code */
int main()
{
    int choice;
    cin >> choice;
    if (choice == 0)
    {
        int n;
        int typeOf;
        cin >> typeOf;

        switch (typeOf)
        {
        case 0:
        {
            int n;
            cin >> n;
            vector<int> arr(n);
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            vector<int> res = map(arr, MapF0());
            for (int i = 0; i < n; i++)
            {
                cout << res[i] << " ";
            }
            cout << endl;

            break;
        }

        case 1:
        {
            int n;
            cin >> n;
            vector<string> arr(n);
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            vector<string> res = map(arr, MapF1());
            for (int i = 0; i < n; i++)
            {
                cout << res[i] << " ";
            }
            cout << endl;

            break;
        }

        case 2:
        {
            int n;
            cin >> n;
            vector<vector<int>> arr(n, vector<int>(n));
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cin >> arr[i][j];
                }
            }
            vector<vector<int>> res = map(arr, MapF2());
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j <= n; j++)
                {
                    cout << res[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            break;
        }
        }
    }

    else
    {
        int typeOf;
        cin >> typeOf;

        switch (typeOf)
        {
        case 0:
        {
            int n;
            cin >> n;
            vector<int> arr(n);
            int ini;
            cin >> ini;
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }

            cout << fold(arr, ini, FoldOp0()) << endl;
            break;
        }

        case 1:
        {
            int n;
            cin >> n;
            vector<int> arr(n);
            string ini;
            cin >> ini;
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            cout << fold(arr, ini, FoldOp1()) << endl;
            break;
        }

        case 2:
        {
            int n;
            cin >> n;
            vector<vector<int>> arr(n, vector<int>(n));

            vector<int> ini(n);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cin >> arr[i][j];
                }
            }
            for (int i = 0; i < n; i++)
            {
                cin >> ini[i];
            }
            vector<int> res = fold(arr, ini, FoldOp2());

            for (int i = 0; i < res.size(); i++)
            {
                cout << res[i] << " ";
            }

            cout << endl;
            break;
        }
        }
    }
}