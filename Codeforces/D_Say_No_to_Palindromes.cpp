/*

                                                 Time complexity       

->Big O notation is generally used to indicate time complexity of any algorithm
 
let say a function varies as an^2+bn+c then its 
time complexity is O(n^2) since we ignore constants and lower dependecies

if the work can be done in constant time
(like assigning a variable name, adding two integers, taking input / output), the complexity is said to be O(1)



what is the time complexity of followings:
O(n^2+nlogn+n)->...O(n^2)

O(n^2+2^(n))->..O(2^n)
O((n*2^(n))+n!)->...


there is something called as timelimit of question, genrally few seconds(1-5 sec).

1 sec-> safe=5e7,cf=1e8
2 sec-> safe=1e8,cf=2e8
3 sec-> safe=2e8,cf=3e8
 most of the time 1e7-1e8 will work
it also depends on the language(c++ is best) and type of operations you are performing 



for the following timecomplexities estimate the value of n to be worked for 1 sec.
O(n)->1e8
O(n^2)->1e4
O(n^3)->300
O(2^n)->26
O(nlogn)->1e6
O(n!)->

find the time complexities of following codes
1.)
for(int i=0;i<n;i++){
for(int j=i+1;j<n;j++){
//some O(1) opertion
n-1,n-2... 1 
O(n^2)
}
}
TC-->

2.)
given k<=n
int j=0;

for(int i=0;i<n;i=i+j){
  for( j=1;j<k;j++){
  //some O(1) operation
  }
}

TC->
3.)

for(int i=1;i<=n;i=i*2){
1 2 4  8     n=2^k 
  for(int j=1;j<=n;j++){
  //some O(1) operation
  }
}
TC->


4.)

for (int i =  n; i > 0; i /= 2) {
        for (int j = 0; j < i; j++) {
           
}}



TC->

some more results

 n + n/2 + n/3 + n/4 .....  O(nlogn)
 n + n/2 + n/3 + n/5 + n/7 + ... + n/x +... where x is a prime number then O(nloglogn)
 n + n/2 + n/4 + n/8 + .. + n/(2^i) +...    O(2*n)-->O(n)

 no. of primes upto n is approx n/logn


 precomputation and more


given a array of size n (n <=1e5)
then given q queries (q<=1e5)
?1 l,r sum from l to r
?2 l,r xor from l to r
?3 l,r gcd of array if you remove l to r from array


given two string find they are annagram or not 
->use frquency array or sort them

condition for palindrome->






*/