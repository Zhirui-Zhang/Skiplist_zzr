# KV跳表存储引擎

> [参考原项目地址](https://github.com/youngyangyang04/Skiplist-CPP)

本项目基于跳表实现了一个轻量级键值型（key-value）KV存储引擎，使用C++实现。

1. 该存储引擎具有插入数据、删除数据、查询数据、数据展示、数据落盘、文件加载数据，以及数据库大小显示等功能，并集中对这些功能做了测试和演示操作。

2. 在模拟实际并发场景的随机读写环境下进行压力测试，该引擎每秒可处理读请求数（QPS）: 10.42w，每秒可处理写请求数（QPS）: 7.69w。



## 项目文件说明

- skiplist目录中包含node.h和skiplist.h两个头文件，分别定义了跳表的节点和表结构的数据结构类型，并定义跳表的核心功能函数
- store目录用于跳表数据在磁盘中的存储和载入，运行时会生成dumpFile.txt文件
- test目录中的main.cpp文件对该跳表引擎进行了功能测试，包括初始化构造、拷贝、插入、删除、查找、等具体函数调用；stress_test.cpp用于模拟并发线程压力测试，分别模拟读写两种不同操作
- Makefile为main.cpp函数的自动编译脚本
- stress_test.sh为压力测试脚本
- README.md项目文件说明



## 项目演示

```
mkdir skiplist_xxx
cd skiplist_xxx
git clone https://github.com/Zhirui-Zhang/Skiplist_zzr
```

### 功能测试

**接口测试示例**

```C++
skiplist<int, string> my_skiplist(6);
my_skiplist.insert_element(1, "Nancy"); 
my_skiplist.size();
my_skiplist.dump_file();
my_skiplist.search_element(9); 
my_skiplist.display_list();
my_skiplist.delete_element(3);
my_skiplist_backup.load_file();
```

**执行文件**

```makefile
make
./main
```

**测试结果**

![main_test](/home/zzr/Skiplist_zzr/source/main_test.png)

## 压力测试

```shell
# 压力测试包括读/写两种测试，分别封装在main函数的两个模块中
# 单独运行时需注释掉另一个模块
sh stress_test.sh
```

> 跳表高度：18
> 
> 插入数据：10万条
> 
> 数据类型：node<K, V> = node<int, string>

**查找操作（读）**

![search_test](https://github.com/Zhirui-Zhang/Skiplist_zzr/blob/a874f188d706f733e338aa4a95d818501d264932/source/main_test.png)

**插入操作（写）**

![insert_test](https://github.com/Zhirui-Zhang/Skiplist_zzr/blob/1ec544ca73cafb7c6629c87adc6a5ff346a5116c/source/insert_test.png)



## 优化和不足

**优化包括：**

- 较参考版本相比，新增了跳表析构函数中所有节点的释放操作，优化了delete_element()功能和随机取高函数get_random_level()，避免发生内存泄漏

- 压力测试脚本无需基于内存中的数据进行读操作，而是利用定义的load_file()函数接口，载入数据后在进行压力测试，便于区分读/写测试环节

**不足：**

- 测试中跳表采用的键值key类型均为int型，如果采用其他类型或者自定义的结构类，需要重载比较运算符，同时适当修改load_file()函数中key值的插入操作
