#include <bits/stdc++.h>
#define pb push_back
#define pf push_front
#define pob pop_back
#define fp first
#define sp second
#define mp make_pair
#define ins insert
#define uEdge(u, v) g[u].pb(v), g[v].pb(u)
#define uwEdge(u, v, w) g[u].pb({v, w}), g[v].pb({u, w})
#define dEdge(u, v) g[u].pb(v)
#define dwEdge(u, v, w) g[u].pb({v, w})
#define BOOST ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define minHeap int, vector<int>, greater<int>
#define MOD 1000000007

using namespace std;
typedef long long int lli;
typedef pair<int, int> pii;
lli nl, arr[0];
vector<int> g[0];

lli gcd(lli a, lli b){if(b == 0) return a;a%=b;return gcd(b, a);}
lli lcm(lli a, lli b){return (a*b)/gcd(a, b);}
int bs(lli sum){int l=0,r=nl-1,mid;while(l<=r){mid=(l+r)/2;if(arr[mid]==sum)return mid;if(arr[mid]<sum)l=mid+1;else r=mid-1;}return -1;}
lli modPow(lli a, lli b){a%=MOD;lli ans=1;while(b > 0){if(b & 1) ans=ans*a%MOD;a=a*a%MOD;b>>=1;}return ans;}

int main(){
    int n, l[100010], cnt=0;
    lli sum=0, sum2=0;
    set<lli> psum;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &l[i]), psum.insert(sum), sum+=l[i];
    if(sum % 2 == 1) printf("N\n");
    else{
        for(int i = 1; i <= n; i++){
            sum2+=l[i];
            if(psum.find((sum2+sum/2)%sum) != psum.end()) cnt++;
        }
        if(cnt >= 4) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
