// RUN: %clang_cc1 -triple x86_64-linux-gnu -std=c++11 -emit-llvm -o - %s | FileCheck %s --check-prefix=CHECK-STATIC-BL
// RUN: %clang_cc1 -triple x86_64-linux-gnu -std=c++11 -emit-llvm -o - %s -Dconstexpr= | FileCheck %s --check-prefix=CHECK-DYNAMIC-BL
// RUN: %clang_cc1 -triple x86_64-linux-gnu -std=c++11 -emit-llvm -o - %s -DUSE_END | FileCheck %s --check-prefix=CHECK-STATIC-BE
// RUN: %clang_cc1 -triple x86_64-linux-gnu -std=c++11 -emit-llvm -o - %s -DUSE_END -Dconstexpr= | FileCheck %s --check-prefix=CHECK-DYNAMIC-BE

namespace std {
  typedef decltype(sizeof(int)) size_t;

  template <class _E>
  class initializer_list
  {
    const _E* __begin_;
#ifdef USE_END
    const _E* __end_;
#else
    size_t    __size_;
#endif

    constexpr initializer_list(const _E* __b, size_t __s)
      : __begin_(__b),
#ifdef USE_END
        __end_(__b + __s)
#else
        __size_(__s)
#endif
    {}

  public:
    typedef _E        value_type;
    typedef const _E& reference;
    typedef const _E& const_reference;
    typedef size_t    size_type;

    typedef const _E* iterator;
    typedef const _E* const_iterator;

#ifdef USE_END
    constexpr initializer_list() : __begin_(nullptr), __end_(nullptr) {}

    size_t    size()  const {return __end_ - __begin_;}
    const _E* begin() const {return __begin_;}
    const _E* end()   const {return __end_;}
#else
    constexpr initializer_list() : __begin_(nullptr), __size_(0) {}

    size_t    size()  const {return __size_;}
    const _E* begin() const {return __begin_;}
    const _E* end()   const {return __begin_ + __size_;}
#endif
  };
}

std::initializer_list<std::initializer_list<int>> nested = {
  {1, 2}, {3, 4}, {5, 6}
};

// CHECK-STATIC-BL: @_ZGR6nested = private constant [2 x i32] [i32 1, i32 2], align 4
// CHECK-STATIC-BL: @_ZGR6nested1 = private constant [2 x i32] [i32 3, i32 4], align 4
// CHECK-STATIC-BL: @_ZGR6nested2 = private constant [2 x i32] [i32 5, i32 6], align 4
// CHECK-STATIC-BL: @_ZGR6nested3 = private constant [3 x {{.*}}] [
// CHECK-STATIC-BL:   {{.*}} { i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested, i32 0, i32 0), i64 2 },
// CHECK-STATIC-BL:   {{.*}} { i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i32 0, i32 0), i64 2 },
// CHECK-STATIC-BL:   {{.*}} { i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i32 0, i32 0), i64 2 }
// CHECK-STATIC-BL: ], align 8
// CHECK-STATIC-BL: @nested = global {{.*}} { {{.*}} getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested3, i32 0, i32 0), i64 3 }, align 8

// CHECK-DYNAMIC-BL: @nested = global
// CHECK-DYNAMIC-BL: @_ZGR6nested = private global [3 x
// CHECK-DYNAMIC-BL: @_ZGR6nested1 = private global [2 x i32] zeroinitializer
// CHECK-DYNAMIC-BL: @_ZGR6nested2 = private global [2 x i32] zeroinitializer
// CHECK-DYNAMIC-BL: @_ZGR6nested3 = private global [2 x i32] zeroinitializer
// CHECK-DYNAMIC-BL: store i32 1, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i64 0, i64 0)
// CHECK-DYNAMIC-BL: store i32 2, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i64 0, i64 1)
// CHECK-DYNAMIC-BL: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i64 0, i64 0),
// CHECK-DYMAMIC-BL:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 0, i32 0), align 8
// CHECK-DYNAMIC-BL: store i64 2, i64* getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 0, i32 1), align 8
// CHECK-DYNAMIC-BL: store i32 3, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i64 0, i64 0)
// CHECK-DYNAMIC-BL: store i32 4, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i64 0, i64 1)
// CHECK-DYNAMIC-BL: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i64 0, i64 0),
// CHECK-DYNAMIC-BL:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 1, i32 0), align 8
// CHECK-DYNAMIC-BL: store i64 2, i64* getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 1, i32 1), align 8
// CHECK-DYNAMIC-BL: store i32 5, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested3, i64 0, i64 0)
// CHECK-DYNAMIC-BL: store i32 6, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested3, i64 0, i64 1)
// CHECK-DYNAMIC-BL: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested3, i64 0, i64 0),
// CHECK-DYNAMIC-BL:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 2, i32 0), align 8
// CHECK-DYNAMIC-BL: store i64 2, i64* getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 2, i32 1), align 8
// CHECK-DYNAMIC-BL: store {{.*}}* getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 0),
// CHECK-DYNAMIC-BL:       {{.*}}** getelementptr inbounds ({{.*}}* @nested, i32 0, i32 0), align 8
// CHECK-DYNAMIC-BL: store i64 3, i64* getelementptr inbounds ({{.*}}* @nested, i32 0, i32 1), align 8

// CHECK-STATIC-BE: @_ZGR6nested = private constant [2 x i32] [i32 1, i32 2], align 4
// CHECK-STATIC-BE: @_ZGR6nested1 = private constant [2 x i32] [i32 3, i32 4], align 4
// CHECK-STATIC-BE: @_ZGR6nested2 = private constant [2 x i32] [i32 5, i32 6], align 4
// CHECK-STATIC-BE: @_ZGR6nested3 = private constant [3 x {{.*}}] [
// CHECK-STATIC-BE:   {{.*}} { i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested, i32 0, i32 0),
// CHECK-STATIC-BE:            i32* bitcast (i8* getelementptr (i8* bitcast ([2 x i32]* @_ZGR6nested to i8*), i64 8) to i32*) }
// CHECK-STATIC-BE:   {{.*}} { i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i32 0, i32 0),
// CHECK-STATIC-BE:            i32* bitcast (i8* getelementptr (i8* bitcast ([2 x i32]* @_ZGR6nested1 to i8*), i64 8) to i32*) }
// CHECK-STATIC-BE:   {{.*}} { i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i32 0, i32 0),
// CHECK-STATIC-BE:            i32* bitcast (i8* getelementptr (i8* bitcast ([2 x i32]* @_ZGR6nested2 to i8*), i64 8) to i32*) }
// CHECK-STATIC-BE: ], align 8
// CHECK-STATIC-BE: @nested = global {{.*}} { {{.*}} getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested3, i32 0, i32 0),
// CHECK-STATIC-BE:                           {{.*}} bitcast ({{.*}}* getelementptr (i8* bitcast ([3 x {{.*}}]* @_ZGR6nested3 to i8*), i64 48) to {{.*}}*) }

// CHECK-DYNAMIC-BE: @nested = global
// CHECK-DYNAMIC-BE: @_ZGR6nested = private global [3 x
// CHECK-DYNAMIC-BE: @_ZGR6nested1 = private global [2 x i32] zeroinitializer
// CHECK-DYNAMIC-BE: @_ZGR6nested2 = private global [2 x i32] zeroinitializer
// CHECK-DYNAMIC-BE: @_ZGR6nested3 = private global [2 x i32] zeroinitializer
// CHECK-DYNAMIC-BE: store i32 1, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i64 0, i64 0)
// CHECK-DYNAMIC-BE: store i32 2, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i64 0, i64 1)
// CHECK-DYNAMIC-BE: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i64 0, i64 0),
// CHECK-DYMAMIC-BE:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 0, i32 0), align 8
// CHECK-DYNAMIC-BE: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested1, i64 1, i64 0),
// CHECK-DYMAMIC-BE:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 0, i32 1), align 8
// CHECK-DYNAMIC-BE: store i32 3, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i64 0, i64 0)
// CHECK-DYNAMIC-BE: store i32 4, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i64 0, i64 1)
// CHECK-DYNAMIC-BE: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i64 0, i64 0),
// CHECK-DYNAMIC-BE:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 1, i32 0), align 8
// CHECK-DYNAMIC-BE: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested2, i64 1, i64 0),
// CHECK-DYNAMIC-BE:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 1, i32 1), align 8
// CHECK-DYNAMIC-BE: store i32 5, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested3, i64 0, i64 0)
// CHECK-DYNAMIC-BE: store i32 6, i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested3, i64 0, i64 1)
// CHECK-DYNAMIC-BE: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested3, i64 0, i64 0),
// CHECK-DYNAMIC-BE:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 2, i32 0), align 8
// CHECK-DYNAMIC-BE: store i32* getelementptr inbounds ([2 x i32]* @_ZGR6nested3, i64 1, i64 0),
// CHECK-DYNAMIC-BE:       i32** getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 2, i32 1), align 8
// CHECK-DYNAMIC-BE: store {{.*}}* getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 0, i64 0),
// CHECK-DYNAMIC-BE:       {{.*}}** getelementptr inbounds ({{.*}}* @nested, i32 0, i32 0), align 8
// CHECK-DYNAMIC-BE: store {{.*}}* getelementptr inbounds ([3 x {{.*}}]* @_ZGR6nested, i64 1, i64 0),
// CHECK-DYNAMIC-BE:       {{.*}}** getelementptr inbounds ({{.*}}* @nested, i32 0, i32 1), align 8
