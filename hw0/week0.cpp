#include<iostream>
#include<string>
using namespace std;
int main(){
    int i,length;
    bool isPalindrome=true;
    string text;
    cin>>text;
    length=text.size();
    for(i=0;i<length/2;i++){
        if(text[i]!=text[length-i-1]){
            isPalindrome=false;
            break;
        }
    }
    if(isPalindrome) cout<<text<<" is a palindrome number.";
    else cout<<text<<" is not a palindrome number.";
}
