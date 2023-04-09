#include <vector>
#include <tuple>
#include <queue>
#include <iostream>
/* Problem:
Given a 2D grid of size m*n, containing 0 (empty space) and 1 (obstacle),
determine the shortest path from the coordinate {0,0} to {m-1,n-1},
given that you can remove upto k obstacles.

If no path exists, return -1.
*/
const int obstacle=1;
typedef struct{
    std::tuple<int,int> coord;
    int obstacleRoute;
    int countSteps;
} registerGrid;

// Your solution
int shortest_path(const std::vector<std::vector<int>>& grid, int k) {
    registerGrid point;
    point.coord=std::make_tuple(0,0);
    point.obstacleRoute=grid[0][0];
    point.countSteps=0;
    std::queue<registerGrid>paths;
    paths.push(point);
    std::tuple<int,int> moves[5] = {{-1,0},{1,0},{0,1},{0,-1}};
    int xGoal=grid.size();
    int yGoal=grid[0].size();
    std::vector<int> aux_grid(yGoal);
    std::fill(aux_grid.begin(),aux_grid.end(),k+1);
    std::vector<std::vector<int>> grid_k(xGoal);
    fill(grid_k.begin(),grid_k.end(),aux_grid);
     if (k<0) {
        return -1;
    }

    if((xGoal == 1 ) && (yGoal == 1)){
        if (grid[0][0]>k){
            return -1;
        }else{
            return 0;
        }
    }
    grid_k[0][0]=point.obstacleRoute;
    while(!paths.empty()){
        for (auto move : moves){
            point=paths.front();
            point.coord=std::make_tuple(std::get<0>(point.coord)+std::get<0>(move),
                                            std::get<1>(point.coord)+std::get<1>(move));
            point.countSteps++;
            if(std::get<0>(point.coord)>=0 && std::get<1>(point.coord)>=0){
                if((std::get<0>(point.coord)< xGoal && std::get<1>(point.coord) < yGoal)){
                    point.obstacleRoute = point.obstacleRoute + grid[std::get<0>(point.coord)][std::get<1>(point.coord)];
                    if (point.obstacleRoute <= k){
                        if ((std::get<0>(point.coord)==xGoal-1)&&(std::get<1>(point.coord)==yGoal-1)){
                            return point.countSteps;
                        }else{
                            if(point.obstacleRoute<grid_k[std::get<0>(point.coord)][std::get<1>(point.coord)]){
                                grid_k[std::get<0>(point.coord)][std::get<1>(point.coord)]=point.obstacleRoute;
                                paths.push(point);
                            }
                        }
                    }
                }
            }
        }
        paths.pop();
    }
    return -1;
}

#include <cassert>

int main() {
    std::vector<std::vector<int>> t0{{0}};
    assert(shortest_path(t0,0) == 0);

    std::vector<std::vector<int>> t1{{0,0,0},{0,0,0},{0,0,0}};
    std::cout << shortest_path(t1,0) << "\n";
    assert(shortest_path(t1,0) == 4);
    assert(shortest_path(t1,1) == 4);

    std::vector<std::vector<int>> t2{{0,1,0},{0,1,0},{0,1,0}};
    assert(shortest_path(t2,0) == -1);
    assert(shortest_path(t2,1) == 4);
    assert(shortest_path(t2,2) == 4);

    std::vector<std::vector<int>> t3{{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
    assert(shortest_path(t3,0) == 8);
    assert(shortest_path(t3,1) == 8);

    std::vector<std::vector<int>> t4{{0,1,0,1,0},{0,1,0,1,0},{0,1,0,1,0},{0,1,0,1,0},{0,1,0,1,0}};
    assert(shortest_path(t4,0) == -1);
    assert(shortest_path(t4,1) == -1);
    assert(shortest_path(t4,2) == 8);
    assert(shortest_path(t4,3) == 8);

    std::vector<std::vector<int>> t5{{0,1,0,1,0},{0,1,1,1,1},{0,1,0,1,0},{0,1,1,1,1},{0,1,0,1,0}};    
    assert(shortest_path(t5,0) == -1);
    assert(shortest_path(t5,1) == -1);
    assert(shortest_path(t5,2) == 8);
    assert(shortest_path(t5,3) == 8);
}