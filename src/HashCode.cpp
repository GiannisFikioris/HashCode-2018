#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <deque>
#include <algorithm>
#include <queue>

using namespace std;

int R,C,F,N,B,T;

int dist(int x1,int y1,int x2,int y2){
	return abs(x1-x2)+abs(y1-y2);
}

class ride {
public:
	int a,b,x,y,s,f,num;

	ride(int aa,int bb,int xx,int yy,int ss,int ff,int nnum){
		a=aa;
		b=bb;
		x=xx;
		y=yy;
		s=ss;
		f=ff;
		num=nnum;
	}

	int ddist(){
		return dist(a,b,x,y);
	}
};

class taxi {
public:
	deque<int> rides;
	int avail;
	int endx;
	int endy;
};

bool com(ride a,ride b){
	return a.s<b.s;
}

class compare{
public:
	bool operator() (taxi a, taxi b){
		return a.avail > b.avail;
	}
};

deque <ride> q;
priority_queue<taxi, vector<taxi>, compare> taxis;


int main() {

	int ee = 2;

	string si,so;
	switch(ee) {
	case 0: si="a_example.in";so="a_example.out"; break;
	case 1: si="b_should_be_easy.in";so="b_should_be_easy.out"; break;
	case 2: si="c_no_hurry.in";so="c_no_hurry.out"; break;
	case 3: si="d_metropolis.in";so="d_metropolis.out"; break;
	case 4: si="e_high_bonus.in";so="e_high_bonus.out"; break;
	}

	int i,a,b,x,y,f,s;
	ifstream inf(si);
	if(inf.is_open()){
		cout << "open\n";
	}
	else {
		cout << "close";
		return -1;
	}
	inf >> R >> C >> F >> N >> B >> T;

	for(i=0;i<N;i++){

		inf >> a >> b >> x >> y >> s >> f;
		ride temp(a,b,x,y,s,f,i);
		q.push_back(temp);

	}
	inf.close();

	sort(q.begin(),q.end(),com);

	for(i=0;i<F;i++){
		taxi temp;
		temp.endx = 0;
		temp.endy = 0;
		temp.avail= 0;
		taxis.push(temp);
	}


	long total=0;

	while(taxis.top().avail<T && q.size()>0){
		taxi temp=taxis.top();
		taxis.pop();
		long long bestnum = -2000000000000000000;
		int bestpos = -1;
		for(i=0;i<q.size();i++){
			if( max(dist(temp.endx,temp.endy,q[i].a,q[i].b) + temp.avail ,q[i].s)+q[i].ddist() >= q[i].f){
				continue;
			}
			long long tempnum = q[i].ddist();
			if (dist(temp.endx,temp.endy,q[i].a,q[i].b)+temp.avail < q[i].s){
				tempnum += B;
			}
			tempnum -= (dist(temp.endx,temp.endy,q[i].a,q[i].b) + max(q[i].s- (dist(temp.endx,temp.endy,q[i].a,q[i].b) + temp.avail),0))*200;
			if(tempnum > bestnum ) {
				bestpos = i;
				bestnum = tempnum;
			}
		}
		if(bestpos < 0) {
			temp.avail = T+2;
			taxis.push(temp);
			continue;
		}
		total += q[bestpos].ddist();
		if (dist(temp.endx,temp.endy,q[bestpos].a,q[bestpos].b)+temp.avail <= q[bestpos].s){
			total += B;
		}
		temp.rides.push_back(q[bestpos].num);

		temp.avail = max(dist(temp.endx,temp.endy,q[bestpos].a,q[bestpos].b)+temp.avail,q[bestpos].s)+q[bestpos].ddist();

		temp.endx = q[bestpos].x;
		temp.endy = q[bestpos].y;
		taxis.push(temp);
		q.erase(q.begin()+bestpos);
	}

	ofstream outf(so);
	while(!taxis.empty()){
		taxi temp = taxis.top();
		taxis.pop();
		outf << temp.rides.size() << " ";
		for(int i = 0; i < temp.rides.size(); i++) {
			outf << temp.rides[i] << " ";
		}
		outf << endl;
	}
	outf.close();

	cout << total;

	return 0;
}
