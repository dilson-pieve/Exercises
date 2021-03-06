// Nice ways calculate product 2 numbers (10^250) (string or lattice multiplication)
// codigo from: https://quickgrid.wordpress.com/tag/uva-problem-10106-product-solution/

//way 1
#include <bits/stdc++.h>

using namespace std;


string multiply(string num1, string num2){

  int n1 = num1.size(), idx_1 = 0;
  int n2 = num2.size(), idx_2 = 0;

  if(n1 == 0 || n2 == 0)
    return "0";

  vector< int > result(n1 + n2, 0);

  for(int i = n1-1; i>=0; i--){
    int carry = 0;
    int x = num1[i] - '0';

    idx_2 = 0;
    for(int j = n2-1; j>=0; j--){
      int y = num2[j] - '0';

      int sum = x*y + result[idx_1 + idx_2] + carry;

      carry = sum/10;
      result[idx_1 + idx_2] = sum%10;

      idx_2 ++;
    }

    if(carry > 0) 
      result[idx_1 + idx_2] += carry;

    idx_1++;
  }

  int i = result.size() - 1;
  while(i>=0 && result[i] == 0)
    i--;

  if(i <= -1)
    return "0";

  string ans = "";
  while(i>=0)
    ans += (to_string(result[i--]));

  return ans;
}

int main() {
   
  string x, y;
  while(cin >> x >> y){
    cout << multiply(x, y) << endl;
  }
  
  return 0;
}


//WAY 2
#include<stdio.h>
#include<string.h>
  
#define M 260
 
struct multiplicationTable{
    int upper;
    int lower;
};
struct multiplicationTable node[M][M];
 
static char string1[M];
static char string2[M];
 
int sum, m, N;


//get sum
int recursiveAdder( int i, int j ){
    if( j < 0 || i >= N )
        return sum;
 
    int val;
    if( m % 2 ){
        val = node[i][j].upper;
        j = j - 1;
    }
    else{
        val = node[i][j].lower;
        i = i + 1;
    }
    ++m;
    sum = sum + val;
    recursiveAdder(i,j);
 
    return sum;
}
 
int main(){
 
    while( gets(string1) ){
        gets(string2);
 
        int len1 = strlen(string1);
        int len2 = strlen(string2);
        
        //same length
        if( len1 > len2 ){
            N = len1;
 
            int shiftWidth = len1 - len2;
 
            for( int i = len1 - 1; i >= 0; --i )
                string2[i + shiftWidth] = string2[i];
 
            for(int j = 0; j < shiftWidth; ++j)
                string2[j] = '0';
 
        }
        else if(len2 > len1){
            N = len2;
 
            int shiftWidth = len2 - len1;
 
            for( int i = len2 - 1; i >= 0; --i )
                string1[i + shiftWidth] = string1[i];
 
            for(int j = 0; j < shiftWidth; ++j)
                string1[j] = '0';
 
        }
        else N = len1; //case igual
 
        int k = N - 1;

        //multiple and guard upper and lower
        for( int i = 0; string2[i]; ++i ){
            for( int j = 0; string2[j]; ++j ){
 
                int num1 = string1[k] - '0';
                int num2 = string2[j] - '0';
 
                int multiply = num1 * num2;
 
                node[j][k].upper = multiply / 10;
                node[j][k].lower = multiply % 10;
 
            }
            --k;
        }
        int upperHalfResult[N];
        
        int i = N - 1;
        for(; i >= 0; --i){
            sum = 0;
            m = 1;

            //sum upper;
            upperHalfResult[i] = recursiveAdder(0, i);
        }
 
        int lowerHalfResult[N];
        i = 0;
        for(; i < N; ++i){
            sum = 0;
            m = 0;

            //sum lower;
            lowerHalfResult[i] = recursiveAdder(i, N - 1);
        }
 
        int combinedRawResult[N + N];
        i = 0;

        //sum upper + sum lower;
        for(; i < N; ++i )
            combinedRawResult[i] = upperHalfResult[i];
        for(k = 0; i < N + N; ++i, ++k )
            combinedRawResult[i] = lowerHalfResult[k];
        
        for( int i = N + N - 1; i >= 0; --i ){
 
            //ajust
            if( combinedRawResult[i] > 9 ){
                combinedRawResult[i - 1] = combinedRawResult[i - 1] + combinedRawResult[i] / 10;
                combinedRawResult[i] = combinedRawResult[i] % 10;
            }
 
        }

        //jump zeros
        for(i = 0; i < N + N; ++i)
            if(combinedRawResult[i]) 
                break;
 
        bool zero = true;
        for(; i < N + N; ++i){
            printf("%d", combinedRawResult[i]);
            zero = false;
        }
        if( zero )
            printf("0");
 
        printf("\n");
 
 
 
    }
 
    return 0;
}
