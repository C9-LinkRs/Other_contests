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

struct pt {
    double x, y;
    pt(double x, double y){
        this->x=x;
        this->y=y;
    }
};

bool onSegment(pt p, pt q, pt r) { //Ver si el punto Q cae en la linea PR
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;
    return false;
}

/*
    Diferencia de los distintos valores de la orientacion de un triple:
    Cero = que el triple es colineal
    Positivo = que el triple tiene orientacion contraria al reloj
    Negativo = que el triple tiene orientacion a favor al reloj
*/

int orientation(pt p, pt q, pt r){
    int val = (q.y-p.y)*(r.x-q.x)-(q.x-p.x)*(r.y-q.y);
    if(val == 0) return 0;
    return (val > 0)? 1: 2;
}

bool has_intersection_point(pt p1, pt q1, pt p2, pt q2){ //Ver si dos lineas se intersectan
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if(o1 != o2 && o3 != o4) return true; //Caso general
    //Casos especiales
    if(o1 == 0 && onSegment(p1, p2, q1)) return true;
    if(o2 == 0 && onSegment(p1, q2, q1)) return true;
    if(o3 == 0 && onSegment(p2, p1, q2)) return true;
    if(o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;
}

bool is_inside(pt test, vector<pt> poly){ //Ver si un punto est� contenido dentro de un poligono convexo
    int i;
    int j;
    bool result = false;
    for(i = 0, j = poly.size()-1; i < poly.size(); j = i++){
        if((poly[i].y > test.y) != (poly[j].y > test.y) &&
            (test.x < (poly[j].x-poly[i].x)*(test.y-poly[i].y)/(poly[j].y-poly[i].y)+poly[i].x))
        {
            result = !result;
        }
    }
    return result;
}

/*
    Implementacion para saber si dos poligonos convexos se intersectan entre si.
    1) La primera parte consiste en verificar si alguna arista del poligono A est� intersectando a otra del poligono B.
    2) La segunda parte consiste en que si no se pudo encontrar que el poligono A se intersecta con el poligono B, entonces
       se buscar� si alg�n punto del poligino A est� contenido dentro el poligono B y viceversa
*/

bool ch_interset(vector<pt> a, vector<pt> b){
    //Primera parte
    for(int i = 0; i < a.size(); i++){
        int nexta=(i+1 == a.size())?0:i+1;
        pt l1p1=a[i], l1p2=a[nexta];
        for(int j = 0; j < b.size(); j++){
            int nextb=(j+1 == b.size())?0:j+1;
            if(has_intersection_point(l1p1, l1p2, b[j], b[nextb])) return true;
        }
    }
    //Segunda parte
    for(int i = 0; i < a.size(); i++) if(is_inside(a[i], b)) return true;
    for(int i = 0; i < b.size(); i++) if(is_inside(b[i], a)) return true;
    return false;
}

/*
    Metodo de Graham para calcular el convex hull de un set de puntos
    con complejidad O(nlogn).
    Esta implementacion ordena los puntos por el eje X y no por angulos polares,
    porque usa la orientacion con el producto vectorial de los 3 puntos.
    Retorna el convex hull en sentido horario empezando por el upper convex hull.
*/

bool cmp(pt a, pt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool clockwise(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool counter_clockwise(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<pt>& a) {
    if(a.size() == 1) return;
    sort(a.begin(), a.end(), &cmp);
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for(int i = 1; i < (int)a.size(); i++){
        if(i == a.size()-1 || clockwise(p1, a[i], p2)){
            while (up.size() >= 2 && !clockwise(up[up.size()-2], up[up.size()-1], a[i])) up.pop_back();
            up.push_back(a[i]);
        }
        if(i == a.size()-1 || counter_clockwise(p1, a[i], p2)){
            while(down.size() >= 2 && !counter_clockwise(down[down.size()-2], down[down.size()-1], a[i])) down.pop_back();
            down.push_back(a[i]);
        }
    }
    a.clear();
    for(int i = 0; i < (int)up.size(); i++) a.push_back(up[i]);
    for(int i = down.size()-2; i > 0; i--) a.push_back(down[i]);
}

int main(){
    int n, r, x, y;
    char type[10];
    while(scanf("%d %d", &n, &r) == 2 && n){
        vector<pt> a, b;
        for(int i = 0; i < n; i++){
            scanf("%d %d %s", &x, &y, type);
            if(type[0] == 'A') a.pb(pt(x, y));
            else if(type[0] == 'B') b.pb(pt(x, y));
        }
        convex_hull(a);
        convex_hull(b);
        if(ch_interset(a, b)) printf("NOT YET\n");
        else printf("FEED\n");
    }
    return 0;
}
