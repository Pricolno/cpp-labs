#ifndef __LINQ_HPP__
#define __LINQ_HPP__

#include <iterator>
#include <utility>
#include <vector>


namespace linq {
  namespace impl {

    template <typename T>
    class take_enumerator; 

    template <typename T, typename F>
    class where_enumerator;

    template<typename T, typename U, typename F>
    class select_enumerator;

    template<typename T>
    class drop_enumerator;
    
    template<typename T, typename F>
    class until_enumerator;

    template<typename T>
    class until_eq_enumerator;

    template <typename T>
    class where_neq_enumerator;
    



    template <typename T>
    class enumerator {
    public:
      enumerator (const enumerator&) = delete;
      enumerator& operator= (const enumerator&) = delete;
      virtual ~enumerator() = default;
      enumerator(enumerator&&) = default;
      enumerator() = default;

      virtual const T& operator* () const = 0;
      virtual enumerator& operator++() = 0;
      virtual operator bool() const = 0;


      auto take(int count) {
        return take_enumerator<T>(*this, count);
      }

      template <typename F>
      auto where(F func) {
        return where_enumerator<T, F>(*this, std::move(func));
      }

      template<typename U = T, typename F>
      auto select(F func) {
        return select_enumerator<U, T, F>(*this, std::move(func));
      }

      auto drop(int count) {
        return drop_enumerator<T>(*this, count);
      }

      template<typename F>
      auto until(F predicate) {
        return until_enumerator<T, F>(*this, std::move(predicate));
      }

      auto until_eq(T var) {
        return until_eq_enumerator<T>(*this, std::move(var));
      }

      auto where_neq(T var) {
        return where_neq_enumerator<T>(*this, std::move(var));
      }



      std::vector<T> to_vector() {
        std::vector<T> result;
        while((bool)*this) {
          result.push_back(**this);
          ++*this;
        }
        return result;
      }

      template<typename Iter>
      void copy_to(Iter&& it) {
        while (*this) {
          *it = *(*this);
          ++it;
          ++(*this);
        }
      }
    };


    template <typename T, typename Iterator>
    class from_enumerator : public enumerator<T> {
    public:
      from_enumerator(Iterator beg, Iterator end) : cur(beg), end(end) {}

      virtual const T& operator* () const override{
        return *cur;
      }
      virtual from_enumerator& operator++() override {
        ++cur;
        return *this;
      }
      virtual operator bool() const override{
        return cur != end;
      }
    private:
      Iterator cur, end;  
    };


    template <typename T>
    class take_enumerator : public enumerator<T> {
    public:
      take_enumerator(enumerator<T>& parent, int count) : count(count), parent(parent) {}
      virtual const T& operator* () const override {
        return *parent;
      }
      virtual take_enumerator& operator++() override{
        --count;
        if(count > 0)
          ++parent;
        return *this;
      }
      virtual operator bool() const override {
        return count > 0 && (bool) parent;
      }
    private:
      int count;
      enumerator<T>& parent;    
    };  

    template <typename T, typename F>
    class where_enumerator : public enumerator<T> {
    public:
      // не совсем лениво, но идейно правильнее. 
      where_enumerator(enumerator<T>& parent, F func) : parent(parent), func(std::move(func)) {
        while(parent && !func(*parent)) {
          ++parent;
        }
      }
      virtual const T& operator* () const override{
        return *parent;
      }
      virtual where_enumerator& operator++()  override{
        ++parent;
        while(parent && !func(*parent)) {
          ++parent;
        }
        return *this;
      }
      virtual operator bool() const override {
        return (bool)parent;
      }
    private:
      enumerator<T>& parent;
      F func;
    };


    template<typename T, typename U, typename F>
    class select_enumerator : public enumerator<T> {
    public:
        select_enumerator(enumerator<U> &parent_, F transform_)
                : transform(std::move(transform_)), parent(parent_) {
          if((bool) parent){
            last = transform(*parent);
          }           
        }

        virtual const T& operator* () const override{
          return last;
        }


        virtual select_enumerator& operator++()  override{
          ++parent;
          if((bool)parent){
            last = transform(*parent);
          }
          return *this;
        }

        virtual operator bool() const override {
          return (bool)parent;
        }

    private:
        F transform;
        enumerator<U> &parent;
        T last;
    };


    template<typename T>
    class drop_enumerator : public enumerator<T> {
    public:
      drop_enumerator(enumerator<T>& parent_, int count_) : count(count_), parent(parent_) {
        //  не очень лениво, но идейно лучше
        while (count > 0 && (bool)parent) {
          ++parent;
          --count;
        }

        if ((bool)parent){
          cur_val = std::move(*parent);
        }
      }

      virtual const T& operator*() const override {
        return cur_val;
      }

      virtual drop_enumerator<T>& operator++() override {
        ++parent;

        if ((bool)parent)
          cur_val = std::move(*parent);

        return *this;
      }

      virtual operator bool() const override {
        return (bool)parent;
      }

    private:
      int count;
      enumerator<T>& parent;
      T cur_val;
    };



    template<typename T, typename F>
    class until_enumerator : public enumerator<T> {
    public:
      until_enumerator(enumerator<T>& parent_, F predicate_) : parent( parent_ ), predicate( std::move(predicate_) ) {
        if ((bool)parent){
          cur_val = std::move(*parent);
        }
      }

      virtual const T& operator*() const override {
        return cur_val;
      }

       virtual until_enumerator<T, F>& operator++() override {
        ++parent;
        
        if ((bool)parent){
          cur_val = std::move(*parent);
        }

        return *this;
      }

      virtual operator bool() const override {
        return (bool)parent && !predicate(cur_val);
      }

    private:
      T cur_val;
      enumerator<T>& parent;
      F predicate;
    };


    template<typename T>
    class until_eq_enumerator : public enumerator<T> {
    public:
      until_eq_enumerator(enumerator<T>& parent_, T val_) : parent( parent_ ), val( val_ ) {
        if ((bool)parent){
          cur_val = std::move(*parent);
        }
      }

      virtual const T& operator*() const override {
        return cur_val;
      }

      virtual until_eq_enumerator& operator++() override {
        ++parent;

        if ((bool)parent){
          cur_val = std::move(*parent);
        }

        return *this;
      }

      virtual operator bool() const override {
        return (bool)parent && cur_val != val;
      }
    private:
      enumerator<T>& parent;
      T val;
      T cur_val;
    };


    template<typename T>
    class where_neq_enumerator : public enumerator<T> {
    public:
      // не очень лениво, но идейно правильнее
      where_neq_enumerator(enumerator<T>& parent_, T var_) : parent( parent_ ), var( std::move(var_) ) {
        while ((bool)parent && *parent == var){
          ++parent;
        }

        if ((bool)parent){
          cur_var = std::move(*parent);
        }
      }

      virtual const T& operator*()  const override {
        return cur_var;
      }

      virtual where_neq_enumerator<T>& operator++() override {
        while ((bool)parent ) {
          ++parent;
          if (*parent != var){
            break; 
          }
        }

        if ((bool)parent){
          cur_var = std::move(*parent);
        }
        return *this;
      }

      virtual operator bool() const override {
        return (bool)parent;
      }

      T cur_var;
      enumerator<T>& parent;
      T var;
    };


  } // namespace impl


   
    

  
  template<typename It>
  auto from(It begin, It end) {
    return std::move(impl::from_enumerator< typename std::iterator_traits<It>::value_type, It>(begin, end));
  } 

} // namespace __LINQ_HPP__

#endif
