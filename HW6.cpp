#include<iostream>
#include<math.h>
#include<map>
#include<queue>
#include<stack>
using namespace std;

struct TreeNode
{
    char data;
    TreeNode* Lchild;
    TreeNode* Rchild;
};
TreeNode Tree[3000006] = {0};
void postorder(TreeNode* root , queue<char> &q);
long long cal(long long n1, long long n2,char op);



int main(){

    map<string,char> convert {
        {"+",'+'},{"-",'-'},{"*",'*'},{"/",'/'},{"1",'1'},{"2",'2'},{"3",'3'},{"4",'4'},{"5",'5'},
        {"6",'6'},{"7",'7'},{"8",'8'},{"9",'9'},{"0",'0'}
    };
    map<char,long long> convert2 {
        {'1',1},{'2',2},{'3',3},{'4',4},{'5',5},
        {'6',6},{'7',7},{'8',8},{'9',9},{'0',0}
    };    
    int height;
    cin >> height;

    //input binary tree
    for(int i = 1; i <= pow(2,height) -1 ; i++){
        string tmp;
        cin >> tmp;
        if(convert.count(tmp)){
            Tree[i].data = convert[tmp];
        }
        else{
            Tree[i].data = '.';
        }
        if((i * 2) <= pow(2,height) -1){
            Tree[i].Lchild = &Tree[i*2];
            if(i*2+1 <= pow(2,height) -1){
                Tree[i].Rchild = &Tree[i*2+1];
            }
            else{
                Tree[i].Rchild = NULL;
            }
        }
        else{
            Tree[i].Lchild = NULL;
        }
    }
    queue<char> postfix;
    postorder(&Tree[1], postfix);
    stack<long long> calculate;

    while (1)
    {
        if(postfix.empty()){
            break;
        }
        else{
            if(convert2.count(postfix.front())){
                calculate.push(convert2[postfix.front()]);
                postfix.pop();
            }
            else{
                long long a,b;
                b = calculate.top();
                calculate.pop();
                a = calculate.top();
                calculate.pop();
                calculate.push(cal(a,b,postfix.front()));
                postfix.pop();
            }
        }
    }
    cout << calculate.top();
    return 0;
}

long long cal(long long n1, long long n2,char op)
{
    if(op == '+'){
        return n1 + n2;
    }
    else if(op == '-'){
        return n1 - n2;
    }
    else if(op == '*'){
        return n1 * n2;
    }
    else if(op == '/'){
        return n1 / n2;
    }
    return 0;
}

void postorder(TreeNode* root, queue<char> &q)
{
    if(root){
        postorder(root->Lchild, q);
        postorder(root->Rchild, q);
        if(root->data != '.'){
            q.push(root->data);
        }
    }
}