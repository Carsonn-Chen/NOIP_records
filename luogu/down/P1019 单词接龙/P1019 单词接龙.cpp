#include<bits/stdc++.h>

using namespace std;

int n,dic[21][21],vis[21],ans;
string words[21];
char s;

void f(string a,string b,int x,int y)
{
    int a1 = a.size()-1,b1 = b.size()-1; 
    for(int i = 0;i <= b1;i ++)  //从第一个开始枚举 
    {
        if(a[0] == b[i])  //如果a的首字母和b中间的字母相同 ，则判断它们能不能接在一起 
        {
            int pos = 0,tot = 0;  //pos是当前a的第几个字母，tot是a和b的重合部分长度 
            for(int j = i;j <= b1;j ++)
            {
                if(a[pos] == b[j])
                {
                    tot ++;
                    pos ++;
                    if(j == b1 && tot != min(a1,b1)+1) //如果枚举到了最后，并且a和b没有包含关系，说明可以这么接 
                      dic[x][y] = tot;  //记录最小重叠部分的长度 
                                      //之所以不break，是因为后面可能还会枚举到更小的接法 
                                      //比如 chsese 和 sesettt 显然 chsesesettt 要比chsesettt更优 
                }
                else break;
            }
        }
    }
}
void dfs(int pos,int sum)
{
    ans = max(ans,sum);  //实时更新ans 
    for(int i = 1;i <= n;i ++)
    {
        if(dic[i][pos] && vis[i])
        {
            vis[i] --;
            int suml = sum+words[i].size()-dic[i][pos]; //接上新单词"龙"的长度为=旧的长度+新单词长度-重复部分长度 
            dfs(i,suml);  //接上新单词继续搜索 
            vis[i] ++;
        }
    }
}
int main()
{
    cin >> n;
    for(int i = 1;i <= n;i ++)
    {
        cin >> words[i];
        vis[i] = 2; //初始化vis数组，每个单词能用两次 
    }   
    cin >> s;
    for(int i = 1;i <= n;i ++)
      for(int j = 1;j <= n;j ++)
        f(words[i],words[j],i,j); //预处理dic数组 

    for(int i = 1;i <= n;i ++)
    {
        if(words[i][0] == s)  //找到开始部分 
        {
            vis[i] --;
            dfs(i,words[i].size()); //深搜 
            vis[i] ++;
        }  
    }
    cout << ans;
    return 0;
}
