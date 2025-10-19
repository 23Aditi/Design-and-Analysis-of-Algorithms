#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct item{
    int id;
    double price;
    double weight;
    double ratio;
    item(int i ,double p , double w){
        id = i;
        price = p;
        weight = w;
        ratio = p/w;
    }
};


void fractional_knapsack(vector<item*>& list, int n, int c){
    sort(list.begin(),list.end(),[](auto& a , auto& b ){
        return a->ratio>b->ratio;
    });
    double totalProfit = 0;
    cout << "ID\tPrice\tWeight\n";
    for(int j = 0 ; j < n ; j++){
        item* i = list[j];
        if(i->weight<=c){
            totalProfit+=i->price;
            c-=i->weight;
            cout << i->id << "\t"<< i->price << "\t"<< i->weight <<"\n";
        }else if(c>0){
            totalProfit += (i->ratio)*c;
            cout << i->id << "\t"<< (i->ratio)*c << "\t"<< c <<"\n";
            break;
        }else{break;}
    }
    cout << "Total profit (fractional knapsack) is : " << totalProfit << "\n";
}

void print_matrix(vector<vector<double>>& matrix,int n , int c){
    for(int i = 0 ; i <=n ; i++){
        for(int j = 0 ; j<=c ; j++){
            cout << setw(4)<< matrix[i][j];
        }
        cout << "\n";
    }
}


void zero_one_knapsack(vector<item*>& list, int n , int c){
    vector<vector<double>> matrix(n+1,vector<double>(c+1,0));
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j<=c ; j++){
            if(j>=(int)list[i-1]->weight){
                matrix[i][j] = max(matrix[i-1][j],list[i-1]->price + matrix[i-1][j-(int)list[i-1]->weight]);
            }else{
                matrix[i][j]=matrix[i-1][j];
            }
        }
    }
    print_matrix(matrix,n,c);
    cout << "Total profit (zero one knapsack) is : " << matrix[n][c] << "\n";
}

int main(){
    int n ;
    cout << "Enter no of items ";
    cin >> n;
    cout << "Enter price and weight of " << n << " items\n";
    vector<item*> list;
    for(int i = 1 ; i<=n ; i++){
        double p,w;
        cin >> p >> w;
        item* it = new item(i,p,w);
        list.push_back(it);
    }
    int c;
    cout << "Enter capacity of the bag : ";
    cin >> c;
    zero_one_knapsack(list,n,c);
    fractional_knapsack(list,n,c);
}


/*

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/DAA (master)
$ ./k
Enter no of items 4
Enter price and weight of 4 items
10 2
30 3
20 5
10 1
Enter capacity of the bag : 4
   0   0   0   0   0
   0   0  10  10  10
   0   0  10  30  30
   0   0  10  30  30
   0  10  10  30  40
Total profit (zero one knapsack) is : 40
ID      Price   Weight
2       30      3
4       10      1
Total profit (fractional knapsack) is : 40

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/DAA (master)
$ ./k
Enter no of items 4  
Enter price and weight of 4 items
10 2
30 3
20 5
10 1
Enter capacity of the bag : 5
   0   0   0   0   0   0
   0   0  10  10  10  10
   0   0  10  30  30  40
   0   0  10  30  30  40
   0  10  10  30  40  40
Total profit (zero one knapsack) is : 40
ID      Price   Weight
2       30      3
4       10      1
1       5       1
Total profit (fractional knapsack) is : 45

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/DAA (master)
$ ./k
Enter no of items 4
Enter price and weight of 4 items
10 2
30 3
20 5
10 1
Enter capacity of the bag : 6
   0   0   0   0   0   0   0
   0   0  10  10  10  10  10
   0   0  10  30  30  40  40
   0   0  10  30  30  40  40
   0  10  10  30  40  40  50
Total profit (zero one knapsack) is : 50
ID      Price   Weight
2       30      3
4       10      1
1       10      2
Total profit (fractional knapsack) is : 50

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/DAA (master)
$ ./k
Enter no of items 4
Enter price and weight of 4 items
10 2 
30 3
20 5
10 1
Enter capacity of the bag : 7
   0   0   0   0   0   0   0   0
   0   0  10  10  10  10  10  10
   0   0  10  30  30  40  40  40
   0   0  10  30  30  40  40  40
   0  10  10  30  40  40  50  50
Total profit (zero one knapsack) is : 50
ID      Price   Weight
2       30      3
4       10      1
1       10      2
3       4       1
Total profit (fractional knapsack) is : 54

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/DAA (master)
$ ./k
Enter no of items 4
Enter price and weight of 4 items
10 2
30 3
20 5
10 1
Enter capacity of the bag : 8
   0   0   0   0   0   0   0   0   0
   0   0  10  10  10  10  10  10  10
   0   0  10  30  30  40  40  40  40
   0   0  10  30  30  40  40  40  50
   0  10  10  30  40  40  50  50  50
Total profit (zero one knapsack) is : 50
ID      Price   Weight
2       30      3
4       10      1
1       10      2
3       8       2
Total profit (fractional knapsack) is : 58

*/


