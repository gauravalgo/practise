#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

class Aggreagate
{
public :
    std::string m_name;
    int m_age;
    
    friend std::ostream& operator<<(std::ostream & os , const Aggreagate & a)
    {
            os << "{" << a.m_name << "," << a.m_age << "}";
            return os;
    }
    
    
};
class NonAggregate
{
private :
    std::string m_name;
    int m_age;
    
public:
    NonAggregate(std::string name="",int age=0):m_name(name),m_age(age){}
    friend std::ostream& operator<< (std::ostream& os ,const NonAggregate & na)
    {
        os<< "{" << na.m_name << "," << na.m_age << "}";
        return os;
    }
    
    void Set (std::string name ,int age )
    {
        this->m_age=age;
        this->m_name=name;
    }
};

void initialization()
{
        NonAggregate a1;
        NonAggregate a2{};
        NonAggregate a3();
        NonAggregate a4{"Steve"};
        NonAggregate a5 {"gaurav",30};
        NonAggregate a6 ("gaurav",30);
        std::cout<< "a1=" << a1 <<std::endl; 
        std::cout<< "a2=" << a2 <<std::endl;
        std::cout<< "a3=" << a3 <<std::endl;
        std::cout<< "a4=" << a4 <<std::endl;
        std::cout<< "a5=" << a5 <<std::endl;
        std::cout<< "a6=" << a6 <<std::endl;
    
}
class Person
{
private:
    int m_age;
    std::string m_name;
public:
        Person(int age=0,std::string name=""):m_name(name),m_age(age){}
        Person (const Person& ) =default;
        Person& operator=(const Person&)=default;
        Person(Person&&) = default;
        Person& operator=(Person&&) = default;
        
    friend std::ostream& operator<<(std::ostream& os,const Person& p)
    {
        
        os<<"I am "<<p.m_name<<","<<p.m_age<<"years old";
        return os;
    }
    
    
};
  
    /// std::clone_unique for single objects
  template<typename _Tp>
      std::unique_ptr<_Tp> clone_unique(const std::unique_ptr<_Tp>& uptr)
    { 
        if(uptr)
        return std::unique_ptr<_Tp>{new _Tp{*uptr}};
        else
        return std::unique_ptr<_Tp>{nullptr};
        
    }
    
    
void test_unique_ptr_with_class_type()
{
    std::unique_ptr<Aggreagate> aptr(new Aggreagate{"Steve",20});
    std::unique_ptr<NonAggregate> nptr(new NonAggregate{"gaurav",30});
    std::cout<< "aptr=" <<*aptr<<std::endl;
    std::cout<< "nptr=" <<*nptr<<std::endl;
   // std::unique_ptr<Aggreagate> aptr1=std::make_unique<Aggreagate>("Steve",20);
   // std::unique_ptr<NonAggregate> nptr1=std::make_unique<NonAggregate>("gaurav",30);
   // std::cout<< "aptr1=" <<*aptr1<<std::endl;
   // std::cout<< "nptr1=" <<*nptr1<<std::endl;
}

void test_reset()
{
        std::unique_ptr<Person> uptr(new Person{20,"hema"});
        std::cout<< " *uptr = " <<*uptr <<std::endl;
        //uptr.reset(); //1. these two statements are the same.
        uptr=nullptr;   //2 .these two statements are the same.
        if(uptr)
        {
            std::cout<<"uptr is valid"<<std::endl;
        }
        else
        {
            std::cout<<"uptr is invalid"<<std::endl;
        }
        uptr.reset(new Person{30,"gaurav sharma"});
        
        std::cout<< "uptr ="<<*uptr<<std::endl;
        
        Person *p =new Person{18,"this is new person"};
        //this is new person 
        uptr.reset(p);
        std::cout<<"new person "<<*uptr<<std::endl;
        /*you cannot assign raw pointer to uniqur pointer*/
        //uptr=p; //only nullptr can be assigned */
        
        
}
void Checkuniqueptrbyrefrence(std::unique_ptr<Person>& uptr)
{
        if(uptr)
        {
            std::cout<<"uptr is valid"<<std::endl;
            std::cout<<*uptr<<std::endl;
            uptr.reset();
        }
        else
        {
            std::cout<<"uptr is invalid"<<std::endl;
        }
    
}
void Checkuniqueptrbyvalue(std::unique_ptr<Person> uptr)
{
        if(uptr)
        {
            std::cout<<"uptr is valid"<<std::endl;
        }
        else
        {
            std::cout<<"uptr is invalid"<<std::endl;
        }
    
}
void test_unique_move()
{
    std::unique_ptr<Person> p = std::make_unique<Person>(60,"the indians do not want to work after 30");
    std::unique_ptr<Person> uptr;
   // uptr=p; this operator does not work for it.
    uptr = std::move(p); //this is possible 
    
    std::cout<<"unique pointer "<<*uptr<<std::endl;
    if(p)
        {
            std::cout<<"uptr is valid"<<std::endl;
        }
        else
        {
            std::cout<<"uptr is invalid"<<std::endl;
        }
    std::unique_ptr<Person> uptr1 =std::make_unique<Person>(14,"my name is gaurav");
    //Checkuniqueptrbyvalue(uptr1); this is not possible because unique pointer cannot be copy constructed or cannot be copy assignment operater is called.
    Checkuniqueptrbyvalue(std::move(uptr1));
    if(uptr1)
        {
            std::cout<<"uptr1 refrence is valid"<<std::endl;
        }
        else
        {
            std::cout<<"uptr1 refrence is invalid"<<std::endl;
        }
    std::unique_ptr<Person> p3 =std::make_unique<Person>(19,"my name is refrence");
    Checkuniqueptrbyrefrence(p3);
    if(p3)
        {
            std::cout<<"uptr refrence is valid"<<std::endl;
            std::cout<<*p3<<std::endl;
        }
        else
        {
            std::cout<<"uptr refrence is invalid"<<std::endl;
            std::cout<<"oh my goodness"<<std::endl;
        }
        
}
void test_clone_unique()
{
    
   std::unique_ptr<Person> p3 =std::make_unique<Person>(13,"cloning unique pte");
    if(p3)
        {
            std::cout<<"uptr refrence is valid"<<std::endl;
            std::cout<<*p3<<std::endl;
        }
        else
        {
            std::cout<<"uptr refrence is invalid"<<std::endl;
            std::cout<<"oh my goodness"<<std::endl;
        }
    std::unique_ptr<Person> p4 =clone_unique(p3);
    if(p4)
        {
            std::cout<<"uptr refrence is valid"<<std::endl;
            std::cout<<*p4<<std::endl;
        }
        else
        {
            std::cout<<"uptr refrence is invalid"<<std::endl;
            std::cout<<"oh my goodness"<<std::endl;
        }
}
void test_and_release()
{
    std::unique_ptr<Person> p{new Person{34,"the great warrior"}};
    Person *p1=p.release();
    delete p1;
   // std::unique_ptr<Person> q=std::make_unique<Person>(p1);
    
}

int main(int argc, char **argv)
{
    initialization();
    //test_unique_ptr_with_class_type();
    test_reset();
    test_unique_move();
    test_clone_unique();
     return 0;
}

