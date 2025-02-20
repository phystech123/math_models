#include<iostream>
#include<cmath>
#include <ostream>
#include<random>


// //first task
// int main(){
//     int k = 0;
//     std::cin >> k;
//     std::random_device r;
//     std::default_random_engine e1(r());
//     std::uniform_int_distribution<int> uniform_dist(1, k);
//     std::cout << uniform_dist(e1) << std::endl;
//     std::cout << uniform_dist(e1) << std::endl;
//     std::cout << uniform_dist(e1) << std::endl;
//     return 0;
// }

// //second task
// int main(){
//     int k = 0;
//     std::cin >> k;
//     std::random_device r;
//     std::default_random_engine e1(r());
//     std::uniform_real_distribution<> uniform_dist(1, k);
//     std::cout << uniform_dist(e1) << std::endl;
//     std::cout << uniform_dist(e1) << std::endl;
//     std::cout << uniform_dist(e1) << std::endl;
//     return 0;
// }

//third task
// int main(){
//     std::random_device r;
//     std::default_random_engine e1(r());
//     std::normal_distribution<> normal_dist(100, 10);
//     for(int i = 0; i < 10; i++){
//         std::cout << normal_dist(e1) << std::endl;
//     }
//     return 0;
// }

//fourth task ---

//fifth task ---

//sixth task
class dist{
    public:
    std::uniform_real_distribution<> uniform_dist1;
    std::uniform_real_distribution<> uniform_dist2;
    dist(int a = -1, int b = 1){
        std::uniform_real_distribution<> uniform_dist1(a, b);
        std::uniform_real_distribution<> uniform_dist2(a, b);
    }
    double operator()(std::mt19937& g){
        std::cout << uniform_dist1(g) << "\n" << uniform_dist2(g) << std::endl;
        return (uniform_dist1(g) + uniform_dist2(g))/2.;
    }
};
int main(){
    int k1 = -1;
    int k2 = 1;
    std::random_device r;
    std::seed_seq seed1{r(), r(),r(),r(),r(),r()};
    std::mt19937 e1(seed1);
    std::mt19937 e2(seed1);
    dist distr(-1, 1);
    std::cout << distr(e1);
   
    
    return 0;
    return 0;
}