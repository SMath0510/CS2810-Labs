#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*Define your Wallet class here*/
class Wallet{
    private:
        vector<int> count;
        vector<string> denomination;
        vector<double> value_of_index;
    public:
    Wallet(){
        for(int denomination_index = 0; denomination_index<15; denomination_index++){
            count.push_back(0);
        }
        denomination = {"2000","500","200","100","50","20n","10n","5n","20c","10c","5c","2","1","0.5","0.25"};
        value_of_index = {2000,500,200,100,50,20,10,5,20,10,5,2,1,0.5,0.25};
    }
    void write(int count_denomination, int denomination_index){
        count[denomination_index] = count_denomination;
    } 
    int read_element_count(int denomination_index){
        return count[denomination_index];
    } 
    void read() const{
        for(int denomination_index = 0; denomination_index<15; denomination_index++){
            cout<<"("<<denomination[denomination_index]<<" "<<count[denomination_index]<<") ";
        }
    }
    operator double () const{
        double sum = 0;
        for(int denomination_index = 0; denomination_index<15; denomination_index++){
            sum+=(value_of_index[denomination_index]*count[denomination_index]);
        }
        return sum;
    }
    int operator [] (double denomination_value){
        int count_of_denomination = 0;
        for(int denomination_index = 0; denomination_index<15; denomination_index++){
            if(value_of_index[denomination_index] == denomination_value){
                count_of_denomination += (count[denomination_index]);
            }
        }
        return count_of_denomination;
    }
    void operator + (Wallet w1){
        for(int denomination_index = 0; denomination_index<15; denomination_index++){
            count[denomination_index] += w1.read_element_count(denomination_index);
        }
    }
    void operator + (double d){
        double to_add = d;
        for(int denomination_index = 0; denomination_index <15; denomination_index++){
            while(to_add >= value_of_index[denomination_index]){
                to_add -= value_of_index[denomination_index];
                count[denomination_index]++;
            }
        }
    }
    void operator - (Wallet w1){
        for(int denomination_index = 0; denomination_index<15; denomination_index++){
            count[denomination_index] -= w1.read_element_count(denomination_index);
        }
    }
    void operator *  (Wallet w1){
        double sum_original = *this;
        double sum_other = w1;
        double sum_final = sum_original*sum_other;
        // double to_add = sum_final - sum_original;
        double to_add = sum_final;
        for(int denomination_index = 14; denomination_index >=0; denomination_index--){
            count[denomination_index] = 0;
        }
        for(int denomination_index = 0; denomination_index <15; denomination_index++){
            while(to_add>= value_of_index[denomination_index]){
                to_add -= value_of_index[denomination_index];
                count[denomination_index]++;
            }
        }
    }
    void operator * (double d){
        double sum_original = *this;
        double sum_final= sum_original*d;
        // double to_add = sum_final - sum_original;
        double to_add = sum_final;
        for(int denomination_index = 14; denomination_index >=0; denomination_index--){
            count[denomination_index] = 0;
        }
        for(int denomination_index = 0; denomination_index <15; denomination_index++){
            while(to_add>= value_of_index[denomination_index]){
                to_add -= value_of_index[denomination_index];
                count[denomination_index]++;
            }
        }
    }
};

istream & operator >> (istream &in, Wallet &w){
    for(int denomination_index = 0; denomination_index<15; denomination_index++){
        int count_denomination;
        cin>>count_denomination;
        w.write(count_denomination, denomination_index);
    }
    return in;
}

ostream & operator << (ostream &out, Wallet &w){
    w.read();
    return out;
}

int main()
{
    int N;
    cin >> N;
    Wallet w,w1;
    int command;
    double d;
    for (int i = 0; i < N; i++)
    {
        cin >> command;
        switch (command)
        {
            case 1: /*initialize wallet*/
                cin >> w;
                break;
            
            case 2: /*print wallet*/
                cout << "Wallet contains: " << w << endl;
                break;
            
            case 3: /*wallet balance*/
                cout << "Wallet has balance: " << (double) w << endl;
                break;
            
            case 4: /*denomination query*/
                cin >> d;
                cout << "Wallet contains " << w[d] << " number of notes/coins of denomination " << d << endl;
                break;
            
            case 5: /*add two wallets*/
                cin >> w1;
                w + w1;
                break;
            
            case 6: /*add money to wallet*/
                cin >> d;
                w + d;
                break;

            case 7: /*subtract from wallet*/
                cin >> w1;
                w - w1;
                break;
            
            case 8: /*multiply wallets*/
                cin >> w1;
                w * w1;
                break;
            
            case 9: /*multiply wallet and double*/
                cin >> d;
                w * d;
                break;

            default:
                break;
        }
    }
}