#include <vector>
#include <iostream>
#include"opencv2/core/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <time.h>
#include<math.h>
using namespace cv;
using namespace std;

struct loc{
	int x ;
	int y ;
	int parent ;
};

Mat img = imread("test.png", 1);
Mat img2 = imread("test.png", 1);
int a = img.rows;
int b = img.cols ;
float stepsize = 30.0 ; 
vector <loc> treest ;
vector <loc> treestend ;
int gap = 10 ;
int startindex = 0 ;
int endindex = 0 ; 

int check1(loc p, loc q){
	loc larger = p, small = q;
	LineIterator it1(img, Point(p.x, p.y), Point(q.x, q.y), 8) ;
	for(int i=0;i<it1.count;i++,++it1){
        Point ret = it1.pos();
        int x3 = ret.x;
        int y3 = ret.y;
        for(int i = -1*gap; i <= gap ; i++){
        	for(int j = -1*gap ; j <= gap ; j++){
        		if(img.at<Vec3b>(y3+i,x3+j)[0] == 255 && img.at<Vec3b>(y3+i,x3+j)[1] == 255 && img.at<Vec3b>(y3+i,x3+j)[2] == 255){
            		return 0; 
        		}
        	}
        }
    }
	return 1;		
}


float node_dist(loc a1, loc b1){
	int x1 = a1.x;
	int y1 = a1.y;
	int x2 = b1.x;
	int y2 = b1.y;
	float d = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	return d ;
}

loc new_loc(loc nnode, loc rnode){
	loc inner, step;
	float magn = 0.0 , X = 0.0, Y = 0.0 ;
	inner.x = rnode.x - nnode.x ;
	inner.y = rnode.y - nnode.y ;
	magn = node_dist(nnode, rnode);
	if(magn > stepsize){
		X = (inner.x/magn);
		Y = (inner.y/magn);
		step.x = (int)(nnode.x + stepsize*X);
		step.y = (int)(nnode.y + stepsize*Y);
		line(img, Point(nnode.x, nnode.y), Point(step.x, step.y) ,Scalar(150,150,150), 2, 8);
		return step ;
	}
	else{
		return rnode ;
	}
	
}

vector <int> start ;
vector <int> endline ;

void end(int sindex, int eindex){
	int p1, p2 ; 
	int i = sindex , j = eindex ;
	start.push_back(sindex) ;
	endline.push_back(eindex) ;
	while(i > 0 && p1 > -1){
		p1 = treest[i].parent ;
		start.push_back(p1) ;
		int flag1 = check1(treest[p1], treest[i]) ;
		line(img2, Point(treest[p1].x, treest[p1].y), Point(treest[i].x, treest[i].y), Scalar(140,100,255),2,8) ;
		i = p1 ;
	 
	}
	while(j > 0 && p2 > -1){
		p2 = treestend[j].parent ;
		endline.push_back(p2) ;
		int flag2 = check1(treestend[p2], treestend[j]) ;
		line(img2, Point(treestend[p2].x, treestend[p2].y), Point(treestend[j].x, treestend[j].y), Scalar(140,100,255),2,8) ;
		j = p2 ;
	
	}
	return  ;
}

int main(){
	srand(time(NULL)) ;
	treestend.clear() ;
	treest.clear() ;
	
	loc endpoint ;
	endpoint.x = 550 ;
	endpoint.y = 550 ;
	endpoint.parent = -1 ;
	treestend.push_back(endpoint) ;
	
	loc startpoint ;
	startpoint.x = 30;
	startpoint.y = 30;
	startpoint.parent = -1 ;
	treest.push_back(startpoint) ;
	cout << endpoint.x << " " << endpoint.y << endl;
	cout << startpoint.x << " " << startpoint.y << endl;

	int count = 0 ;
	while(count == 0){
		loc n1 , n2 , n3;
		int par1 ;
		n1.x = rand()%a ;
		n1.y = rand()%b ;
		float l = 100000.0 ;
		for(int i = 0 ; i < treest.size() ; i++){
			float m = node_dist(n1, treest[i]);
			if( m < l ){
				l = m ;
				n2.x = treest[i].x ;
				n2.y = treest[i].y ;
				par1 = i ;
			}			
		}
		n3 = new_loc(n2, n1) ;
		int r = check1(n3,n1);
		if(r == 1){
				
			n3.parent = par1 ;
			treest.push_back(n3) ; 
			imshow("window", img) ;
			waitKey(50);

		}
		
		loc t1, t2, t3 ;
		int par2 ;
		t1.x = rand()%a ;
		t1.y = rand()%b ;
		float l1 = 100000.0 ;
		for(int i = 0 ; i < treestend.size() ; i++){
			float m = node_dist(t1, treestend[i]);
			if( m < l1 ){
				l1 = m ;
				t2.x = treestend[i].x ;
				t2.y = treestend[i].y ;
				par2 = i ;
			}			
		}	
		t3 = new_loc(t2, t1) ;
		int key = check1(t3, t1) ;
		if(key == 1){	
			t3.parent = par2 ;
			treestend.push_back(t3) ;
			imshow("window", img) ;
			waitKey(50);

		}

		for(int i = 0 ; i < treest.size() ; i++){
			for(int j = 0 ; j < treestend.size(); j++){
				int flag = check1(treestend[j], treest[i]); 
				if(flag == 1){
					line(img, Point(treest[i].x, treest[i].y), Point(treestend[j].x, treestend[j].y), Scalar(140,100,255),2,8);
					line(img2, Point(treest[i].x, treest[i].y), Point(treestend[j].x, treestend[j].y), Scalar(140,100,255),2,8);
					count = 1 ;
					endindex = j ;
					startindex = i ; 
					break ;
				}
			}
			if(count == 1)
					break ;
		}
		

	}
	
	end(startindex, endindex) ;
	
	for(int i = start.size()-1 ; i >= 0; i--){
		cout << treest[start[i]].x / 60.0<< " " << treest[start[i]].y/60.0 << endl;
	}
	for(int j = endline.size()-1 ; j >= 0 ; j--){
		cout << treestend[endline[j]].x / 60.0 << " " << treestend[endline[j]].y/60.0 << endl; 
	}

	imshow("img2", img2) ;
	namedWindow("window", WINDOW_AUTOSIZE) ;
	imshow("window", img) ;
	waitKey(0);
	return 0 ;

}