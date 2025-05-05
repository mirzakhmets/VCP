
#include <stack>
#include <queue>
#include <vector>

#include <cstdio>
#include <cctype>
#include <cstdlib>

#include <algorithm>

using namespace std;

class VertexHolder {
public:
	int index;
	
	int degree;
	
	VertexHolder() : index(-1), degree(0) {
		
	}
	
	VertexHolder& operator= (const VertexHolder &b) {
		this->index = b.index;
		
		this->degree = b.degree;
		
		return *this;
	}
};

bool operator< (const VertexHolder& a, const VertexHolder &b) {
	return a.degree > b.degree;
}

int main(int argc, char** argv) {
	int n, m;
	char buffer[128];
	vector< vector<int> > e;
	vector<VertexHolder> vh;
	bool **bvb = NULL;
	
	//freopen ("C:/VCP/zeroin.i.1.col", "rb", stdin);
	//freopen ("C:/VCP/zeroin.i.2.col", "rb", stdin);
	//freopen ("C:/VCP/zeroin.i.3.col", "rb", stdin);
	//freopen ("C:/VCP/anna.col", "rb", stdin);
	//freopen ("C:/VCP/david.col", "rb", stdin);
	//freopen ("C:/VCP/homer.col", "rb", stdin);
	//freopen ("C:/VCP/huck.col", "rb", stdin);
	//freopen ("C:/VCP/jean.col", "rb", stdin);
	//freopen ("C:/VCP/games120.col", "rb", stdin);
	//freopen ("C:/VCP/miles1000.col", "rb", stdin);
	//freopen ("C:/VCP/miles1500.col", "rb", stdin);
	//freopen ("C:/VCP/miles250.col", "rb", stdin);
	//freopen ("C:/VCP/miles500.col", "rb", stdin);
	//freopen ("C:/VCP/miles750.col", "rb", stdin);
	freopen ("queen13_13.col", "rb", stdin);
	//freopen ("C:/VCP/queen9_9.col", "rb", stdin);
	//freopen ("C:/VCP/fpsol2.i.1.col", "rb", stdin);
	//freopen ("C:/VCP/myciel3.col", "rb", stdin);
	//freopen ("C:/VCP/myciel6.col", "rb", stdin);
	//freopen ("C:/VCP/myciel7.col", "rb", stdin);
	//freopen ("C:/VCP/le450_15b.col", "rb", stdin);
	//freopen ("C:/VCP/inithx.i.1.col", "rb", stdin);
	//freopen ("C:/VCP/inithx.i.1.col", "rb", stdin);
	//freopen ("C:/VCP/le450_5d.col", "rb", stdin);
	//freopen ("C:/VCP/mulsol.i.1.col", "rb", stdin);
	//freopen ("C:/VCP/myciel4.col", "rb", stdin);
	//freopen ("C:/VCP/myciel5.col", "rb", stdin);
	//freopen ("C:/VCP/myciel5.col", "rb", stdin);
	
	while (!feof(stdin)) {
		fgets (buffer, sizeof(buffer), stdin);
		
		if (buffer[0] == 'p') {
			char *p = buffer + 7;
			
			char *pm = p;
			
			while (isdigit(*pm)) ++pm;
			
			*pm++ = '\0';
			
			n = atoi (p);
			
			m = atoi (pm);
			
			e.resize(n);
			
			vh.resize(n);
			
			bvb = new bool* [n];
			
			for (int i = 0; i < n; ++i) {
				bvb[i] = new bool[n];
				
				for (int j = 0; j < n; ++j) {
					bvb[i][j] = false;
				}
			}
		} else if (buffer[0] == 'e') {
			char *p = buffer + 2;
			
			char *pm = p;
			
			while (isdigit(*pm)) ++pm;
			
			*pm++ = '\0';
			
			int a = atoi(p) - 1;
			int b = atoi(pm) - 1;
			
			if (!bvb[a][b]) {
				e[a].push_back(b);
				e[b].push_back(a);
				
				bvb[a][b] = bvb[b][a] = true;
			}
		} else {
			puts(buffer + 2);
		}
	}
	
	printf ("N = %d, M = %d\n", n, m);
	
	int *chromatic = new int [n];
	bool **chrranges = new bool*[n];
	int *chromaticcount = new int[n + 1];

	for (int i = 0; i < n; ++i) {
		chromatic[i] = -1;
		
		chrranges[i] = new bool[n + 1];
		
		for (int j = 0; j <= n; ++j) {
			chrranges[i][j] = false;
		}
		
		vh[i].index = i;
		vh[i].degree = e[i].size();
		
		chromaticcount[i] = 0;
	}
	
	chromaticcount[n] = 0;
	
	sort (vh.begin(), vh.end());
	
	for (int i = 0; i < n; ++i) {
		//int v = vh[i].index;
		
		int v = i;
		
		for (int j = 0; j < n; ++j) {
			chromatic[j] = -1;
			
			for (int k = 0; k < n; ++k) {
				chrranges[j][k] = false;
			}
			
			chromaticcount[i] = 0;
		}
		
		chromaticcount[n] = 0;
		
		int currentmaxchr = -1;
				
		if (chromatic[v] == -1) {
			stack<int> st;
			
			st.push(v);
			
			while (!st.empty()) {
				int a = st.top();
				
				st.pop();
				
				if (chromatic[a] != -1) {
					continue;
				}
				
				for (int j = 0; j < e[a].size(); ++j) {
					if (chromatic[e[a][j]] != -1) {
						chrranges[a][chromatic[e[a][j]]] = true;
					} else {
						st.push(e[a][j]);
					}
				}
				
				/*
					for (int j = currentmaxchr; j >= 0; j -= 4) {
						if (!chrranges[a][j]) {
							chromatic[a] = j;
							
							//chrranges[a][j] = true;
							break;
					}
				
				*/
				if (chromatic[a] == -1) {
					int chromaticindex = -1;
					
					for (int j = 0; j < 13; ++j) {
						if (!chrranges[a][j]) {
							//chromatic[a] = j;
							
							//chrranges[a][j] = true;
							
							//if (j > currentmaxchr) {
								//currentmaxchr = j;
							
								//printf ("PP %d, ", currentmaxchr);
							//}
							
							//break;
						
							
							if (chromaticindex == -1 || chromaticcount[chromaticindex] > chromaticcount[j]) {
								chromaticindex = j;
							}
						}
					}
					
					if (chromaticindex == -1) {
						//printf ("Error\n");
						
						break;
						chromaticindex = currentmaxchr++;
					}
					
					chromatic[a] = chromaticindex;
					
					++chromaticcount[chromaticindex];
					
					//chrranges[a][chromaticindex] = true;
				}
			}
		}
		
		
		bool *bchromatic = new bool[n + 1];
		
		for (int j = 0; j <= n; ++j) {
			bchromatic[j] = false;
		}
		
		bool n1 = false;
		
		for (int j = 0; j < n; ++j) {
			if (chromatic[j] == -1) {
				n1 = true;
				
				break;
			}
			
			bchromatic[chromatic[j]] = true;
			
			//printf ("%d ", chromatic[i]);
		}
	
		if (n1) {
			continue;
		}
		
		int maxchr = 0;
		
		for (int j = 0; j < n; ++j) {
			if (bchromatic[j]) {
				++maxchr;
			}
		}
		
		//printf ("\n");
		
		printf ("%d %d\n", maxchr, e[i].size());
		
	}
	
	/*

		bool *bchromatic = new bool[n + 1];
		
		for (int j = 0; j <= n; ++j) {
			bchromatic[j] = false;
		}
		
		for (int j = 0; j < n; ++j) {
			bchromatic[chromatic[j]] = true;
		}
	
		int maxchr = 0;
		
		for (int j = 0; j < n; ++j) {
			if (bchromatic[j]) {
				++maxchr;
			}
		}
		
		//printf ("\n");
		
		printf ("%d\n", maxchr);

	*/
	
	scanf ("%s", buffer);
	return 0;
}
