#include <iostream>
#include <vector>
using namespace std;

int x[100]; //this array will store 0, 1, up to m-1 and 0,1, up to n-1 respectively, so as to be able to form all the tuples
int x2[100][2]; // this matrix will store all the tuples that can form a solution(subgroup)
int n2, p2;
int c = 0;

bool OK(int k) {
    for (int i = 1; i < k; ++i)
        if (x[k] <= x[i]) // a solution should countain tuples that do not repeat, and the x coordinate and y coordinate are stored in an inccreasing order
            return false;
    return true;
}

bool Solutie(int k, int n)
{
    return k == n; // we check if the solution has the requested number of elements(p2) (the number goes from 1 to the total number of possible elements in a tuple (m*n))
}

// the basic backtracking algorithm for generating permutations
// it returns a new line in the output when the solution is complete
char back(int k, int n) {
    for (int i = 0; i < n; ++i)
    {
        x[k] = i;
        if (OK(k))
            if (Solutie(k, n))
                return '\0';
            else
                return back(k + 1, n);
    }
}
////
bool search(int x_coord, int y_coord, int k) {
    // searches a tuple in the subgroup
    for (int i2 = 1; i2 <= k; ++i2)
        if ((x2[i2][0] == x_coord) && (x2[i2][1] == y_coord))
            return true;
    return false;
}
bool condition(int k, int m, int n) {
    // this function checks the stability of the + in the subgroup, i.e, every element added with any element with respect to the module class should be in the subgropu
    // assume by contr that the subgroup is closed w r t the addition in Zm and Zn and if we find 2 elemeents which go out of the subgroup, we return false
    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= k; ++j) {
            if (!search((x2[i][0] + x2[j][0]) % m, (x2[i][1] + x2[j][1]) % n, k))
                return false;
        }
    return true;
}

void Afis(int k, int m, int n) {
    // printing the solution
    if (condition(k, m, n) && x2[0][0] == 0 && x2[0][1] == 0) {
        for (int i = 1; i <= k; ++i)
            cout << "(" << x2[i][0] << ", " << x2[i][1] << ") ";
        cout << endl;
        c++;
    }
}

/*
 - this function recursively generates and checks all possible subgroups of tuples
 of length p2 from the matrix. It starts from startIndex in the matrix to avoid duplicates and unnecessary computations.
 - here, k is the curent position in the subgroup being constructed.
 */
void back2(int k, const vector<vector<int>>& matrix, int startIndex, int m, int n) {
    if (k == p2 + 1) {
        // check if the subgroup has the requested length( at every step)
        Afis(p2, m, n);
        return;
    }

    for (int i = startIndex; i <= n2 - p2 + k; ++i) {
        //choose the next tuple and call back2 recurisevely to continue forming the subgroup
        x2[k][0] = matrix[i - 1][0];
        x2[k][1] = matrix[i - 1][1];
        back2(k + 1, matrix, i + 1, m, n);
    }
}

int main() {
    int n, m, p;
    cin >> m >> n;
    // defining a vector type matrix so as to be able to work with tuples more easily and print them as tuples (a,b)
    vector<vector<int>> matrix(m * n, vector<int>(2));

    // generate the Zm and Zn classes
    cout << back(1, n) << endl;
    cout << back(1, m) << endl;
    p = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (p < m * n) {
                // store the tuples in the matrix 
                matrix[p][0] = x[i];
                matrix[p][1] = x[j];
                p++;
            }

    n2 = m * n;
    //check for all the subgroups of length 1, 2, up to length m*n, using the backtracking algorithm
    for (int i = 1; i <= m * n; i++) {
        p2 = i;
        back2(1, matrix, 1, m, n);
    }
    cout << endl;
    // print how many subgroups we have
    cout << c;
    return 0;
}
