#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

class Point {
public:
    float x;
    float y;

    Point(float xX, float yY);
    Point calculateDistanceToCenters(Point c1, Point c2);
};

Point::Point(float xX, float yY){
    x = xX;
    y = yY;
}

Point Point::calculateDistanceToCenters(Point c1, Point c2) {
    float distanceC1 = sqrt(pow((x-c1.x),2) + pow((y-c1.y),2));
    float distanceC2 = sqrt(pow((x-c2.x),2) + pow((y-c2.y),2));

    Point result(distanceC1,distanceC2);

    cout<< "X: " << distanceC1 << " Y:" << distanceC2 << endl;
    return result;
}

bool comparePoints(Point a, Point b,Point c1,Point c2){
    cout<<"Comp A C1: "<<a.x << ", " << c1.x << " Y:" << a.y << ", " << c1.y<<endl;
    cout<<"Comp B C2: "<<b.x << ", " << c2.x << " Y:" << b.y << ", " << c2.y<<endl;
    return (a.x == c1.x && a.y == c1.y) && (b.x == c2.x && b.y == c2.y);
}

vector<Point> calculateNewCenters(vector<Point> minX, vector<Point> minY){
    float x = 0;
    float y = 0;

    int minXSize = minX.size();
    int minYSize = minY.size();

    for(int cont = 0 ; cont < minXSize ; cont++){
        x += minX.at(cont).x;
        y += minX.at(cont).y;
    }
    x = x / minXSize;
    y = y / minXSize;
    Point resultC1(x,y);
    x = 0;
    y = 0;
    for(int cont = 0 ; cont < minYSize ; cont++){
        x += minY.at(cont).x;
        y += minY.at(cont).y;
    }
    x = x / minYSize;
    y = y / minYSize;
    Point resultC2(x,y);

    vector<Point> results;
    results.push_back(resultC1);
    results.push_back(resultC2);
    return results;
}

int main() {
    Point a(1,1);
    Point b(2,1);
    Point c(4,3);
    Point d(5,4);

    Point c1(1,1);
    Point c2(2,1);

    vector<Point> points;
    vector<Point> centers;
    vector<Point> results;

    vector<Point> minC1;
    vector<Point> minC2;

    points.push_back(a);
    points.push_back(b);
    points.push_back(c);
    points.push_back(d);

    centers.push_back(c1);
    centers.push_back(c2);

    int pointSize = points.size();


    Point lastResultC1(0,0);
    Point lastResultC2(0,0);
    do{
        cout<<endl;
        if(!results.empty()){
            lastResultC1 = results.front();
            lastResultC2 = results.back();
        }
        for(int cont = 0 ; cont< pointSize ; cont++){
            Point comparision = points.at(cont);
            Point result = comparision.calculateDistanceToCenters(c1, c2);

            if(result.x < result.y){
                cout<< "MinC1 X: "<<result.x << " Y:" << result.y<<endl;
                minC1.push_back(comparision);
            }else{
                cout<< "MinC2 X: "<<result.x << " Y:" << result.y<<endl;
                minC2.push_back(comparision);
            }
        }
        results = calculateNewCenters(minC1,minC2);
        for(int cont = 0 ; cont < results.size() ; cont++){
            cout<< "Result C" << cont + 1<< " X: " << results.at(cont).x << " Y:" << results.at(cont).y<<endl;
        }
        minC1.clear();
        minC2.clear();
        c1 = results.front();
        c2 = results.back();
        cout<<endl;
    }while (!comparePoints(lastResultC1,lastResultC2,results.front(),results.back()));

    return 0;
}