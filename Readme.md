neville algorithms
bivariate langrange interpolation
whimsical
//nov 28 2019
today i am reading variadic templates going native 2012 variadic templates are funadic
https://www.youtube.com/watch?v=_zgq6_zFNGY&t=129s
also i am watching iron man clip 

1) motivation 
    typesafe variadic function printf
    variant (sum type),tuple(product type)
    specify the settings ans paarameters in policy based design
// nov 19 2019 
 topic continued ..
 template<typename... Ts>
 class C
 {
 
 }
 // Ts is not the type you cannot use it directly
 // Vs is not the values you cannot use it directly
 template<typename... Ts>
 void function(Ts&... vs)
 {
    
 }
 
 expansion rules to variadic templates list and list of values
 1) Ts...                T1,...,Tn
 2) Ts&&...              T1&&,...,Tn&&
 3) X<Ts,Y>::z...        X<T1,Y>::z,...,X<Tn,Y>::z
 4) X<Ts&,Y>::z...        X<T1&,Y>::z,...,X<Tn&,Y>::z
 5) func(5,vs)...         func(5,v1),...,func(5,vn)
 
 
 expansion loci(in what context does thee variadic lists expands things)
 
 Intializer list->varidic lists //remember intializer list is the run time expansion and the variadic lists is the compile time expansion
 any a[]={vs...} //auto expansion occurs at compile time
 
 //inheriting from every body also works for the expansion of variadic templates
 template<typename...Ts>
 struct Class : Ts...
 {
 
 };
 
 template<typename... Ts>
 struct Class :Box<Ts>...
 {
 
 };
 
 //Member Intializer lists inside the Class
 
 template<typename... Us>
 D(Us... vs):Box<Ts>(vs)...{} //complicated yet but true to understand
 
 // template argument lists
 
 std::map<Ts...> m; //this forms another type which expands automatically by its own rules.
 
 
 //another thing is attribute lists
 struct[[Ts...]]  IamfromtheFuture{};
 
 //Capture Lists in lambdas
 //good for threads
 template<typename... Ts>
 void fun(Ts ... vs)
 {
    auto g = [&vs ... ]{return gun(vs...);}
    g();
 }
 // writing the expansion matters
 
 template<typename... Ts>
 void fun(Ts... vs)
 {
    gun(A<Ts...>::hun(vs)...); //for each value Ts have to expand again like hun(1),...,hun(n)
    gun(A<Ts...>::hun(vs...)); //for each value of Ts have to expand like A<int>::hun(i),A<int>::hun(j),A<float>::hun(f),....A<typename>::hun(n)
    gun(A<Ts>::hun(vs)...); //for one value Ts have to expand again like hun(1),...,hun(n)
 }
 
 Variadic Variadics Template Templates
 ====================================
 
 
 template<typename T,template < template <class...> class... Policies>> class butter;
 //this works
 
 //compile time recursion
  //two specializations 
  template<typename T,typename U>
  bool isoneof(T t,U u)
  {
    if(t==u)
    return true;
  }
  
  template<typename T,typename U,typename... Ts>
  bool isoneof(T t,U u,Ts... Vs)
  {
    return t==u||isoneof(t,Vs...);
  }
  
  //true variadic functions very important 
  
  1) add adaption routines for type safety for long,double and char
  2) define the base case //error checking check_printf(const char  *f){ return true;}
  3) recursive case template<typename T,typename... Ts>check_printf(const char  *f,Ts&... ts){ return check_printf(*f++,ts...)}
  
  //std::tuple
  //c++ so easy to use  as you can see the memory model of the program.

  1) constructors and assignments for tuple 
  2) make_tuple
  3) equality and odering comparisons
  4) swap
  5) pack arguments
  6) tie
  7) tuple_cat
  8) allocator consatructors uses_allocator
  9) range primitives begin, end
  
  
  //tuple structure
  template<typename T>
  class tuple
  {};
  template<typename T,typename... Ts>
  class tuple:private tuple<Ts...>
  {
    private:
    T head;
    ....
  };
  //recursion in the types
  template<size_t ,class> struct tuple_element;
  template<class T,class... Ts> struct tuple_element<0,tuple<T,Ts...>>
  {
    typedef T type;
  }
  taemplate<size_t k,class T,class... Ts> struct tuple_element<k,tuple<T,Ts...>>
  {
    typedef typename tuple_element<k-1,tuple<Ts...>>::type type;
  }
  
  summary ...
  ===========
  //recursion in the types
  //expansion rules to get values
  //true variadic functions now possible. like type safe printf
  //example tuple
  
  
  
